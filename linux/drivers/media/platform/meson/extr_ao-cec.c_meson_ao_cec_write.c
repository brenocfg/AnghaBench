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
typedef  unsigned long u8 ;
typedef  int u32 ;
struct meson_ao_cec_device {int /*<<< orphan*/  cec_reg_lock; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_RW_ADDR ; 
 scalar_t__ CEC_RW_REG ; 
 int CEC_RW_WRITE_EN ; 
 int /*<<< orphan*/  CEC_RW_WR_DATA ; 
 int FIELD_PREP (int /*<<< orphan*/ ,unsigned long) ; 
 int meson_ao_cec_wait_busy (struct meson_ao_cec_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void meson_ao_cec_write(struct meson_ao_cec_device *ao_cec,
			       unsigned long address, u8 data,
			       int *res)
{
	unsigned long flags;
	u32 reg = FIELD_PREP(CEC_RW_ADDR, address) |
		  FIELD_PREP(CEC_RW_WR_DATA, data) |
		  CEC_RW_WRITE_EN;
	int ret = 0;

	if (res && *res)
		return;

	spin_lock_irqsave(&ao_cec->cec_reg_lock, flags);

	ret = meson_ao_cec_wait_busy(ao_cec);
	if (ret)
		goto write_out;

	writel_relaxed(reg, ao_cec->base + CEC_RW_REG);

write_out:
	spin_unlock_irqrestore(&ao_cec->cec_reg_lock, flags);

	if (res)
		*res = ret;
}