#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct sprd_adi {scalar_t__ hwlock; int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADI_HWSPINLOCK_TIMEOUT ; 
 int ADI_READ_TIMEOUT ; 
 int BIT_RD_CMD_BUSY ; 
 int EBUSY ; 
 int EIO ; 
 int RD_ADDR_MASK ; 
 int RD_ADDR_SHIFT ; 
 int RD_VALUE_MASK ; 
 int REG_ADDR_LOW_MASK ; 
 scalar_t__ REG_ADI_RD_CMD ; 
 scalar_t__ REG_ADI_RD_DATA ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hwspin_lock_timeout_irqsave (scalar_t__,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  hwspin_unlock_irqrestore (scalar_t__,unsigned long*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int sprd_adi_read(struct sprd_adi *sadi, u32 reg_paddr, u32 *read_val)
{
	int read_timeout = ADI_READ_TIMEOUT;
	unsigned long flags;
	u32 val, rd_addr;
	int ret = 0;

	if (sadi->hwlock) {
		ret = hwspin_lock_timeout_irqsave(sadi->hwlock,
						  ADI_HWSPINLOCK_TIMEOUT,
						  &flags);
		if (ret) {
			dev_err(sadi->dev, "get the hw lock failed\n");
			return ret;
		}
	}

	/*
	 * Set the physical register address need to read into RD_CMD register,
	 * then ADI controller will start to transfer automatically.
	 */
	writel_relaxed(reg_paddr, sadi->base + REG_ADI_RD_CMD);

	/*
	 * Wait read operation complete, the BIT_RD_CMD_BUSY will be set
	 * simultaneously when writing read command to register, and the
	 * BIT_RD_CMD_BUSY will be cleared after the read operation is
	 * completed.
	 */
	do {
		val = readl_relaxed(sadi->base + REG_ADI_RD_DATA);
		if (!(val & BIT_RD_CMD_BUSY))
			break;

		cpu_relax();
	} while (--read_timeout);

	if (read_timeout == 0) {
		dev_err(sadi->dev, "ADI read timeout\n");
		ret = -EBUSY;
		goto out;
	}

	/*
	 * The return value includes data and read register address, from bit 0
	 * to bit 15 are data, and from bit 16 to bit 30 are read register
	 * address. Then we can check the returned register address to validate
	 * data.
	 */
	rd_addr = (val & RD_ADDR_MASK ) >> RD_ADDR_SHIFT;

	if (rd_addr != (reg_paddr & REG_ADDR_LOW_MASK)) {
		dev_err(sadi->dev, "read error, reg addr = 0x%x, val = 0x%x\n",
			reg_paddr, val);
		ret = -EIO;
		goto out;
	}

	*read_val = val & RD_VALUE_MASK;

out:
	if (sadi->hwlock)
		hwspin_unlock_irqrestore(sadi->hwlock, &flags);
	return ret;
}