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
typedef  scalar_t__ u8 ;
struct fsi_master_acf {int /*<<< orphan*/  dev; scalar_t__ sram; scalar_t__ cvic; int /*<<< orphan*/  scu; } ;

/* Variables and functions */
 scalar_t__ ARB_ARM_ACK ; 
 scalar_t__ ARB_ARM_REQ ; 
 scalar_t__ ARB_REG ; 
 scalar_t__ CF_STARTED ; 
 scalar_t__ CVIC_TRIG_REG ; 
 unsigned int SCU_COPRO_CLK_EN ; 
 int /*<<< orphan*/  SCU_COPRO_CTRL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 scalar_t__ ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fsi_master_acf_gpio_request(void *data)
{
	struct fsi_master_acf *master = data;
	int timeout;
	u8 val;

	/* Note: This doesn't require holding out mutex */

	/* Write reqest */
	iowrite8(ARB_ARM_REQ, master->sram + ARB_REG);

	/*
	 * There is a race (which does happen at boot time) when we get an
	 * arbitration request as we are either about to or just starting
	 * the coprocessor.
	 *
	 * To handle it, we first check if we are running. If not yet we
	 * check whether the copro is started in the SCU.
	 *
	 * If it's not started, we can basically just assume we have arbitration
	 * and return. Otherwise, we wait normally expecting for the arbitration
	 * to eventually complete.
	 */
	if (ioread32(master->sram + CF_STARTED) == 0) {
		unsigned int reg = 0;

		regmap_read(master->scu, SCU_COPRO_CTRL, &reg);
		if (!(reg & SCU_COPRO_CLK_EN))
			return 0;
	}

	/* Ring doorbell if any */
	if (master->cvic)
		iowrite32(0x2, master->cvic + CVIC_TRIG_REG);

	for (timeout = 0; timeout < 10000; timeout++) {
		val = ioread8(master->sram + ARB_REG);
		if (val != ARB_ARM_REQ)
			break;
		udelay(1);
	}

	/* If it failed, override anyway */
	if (val != ARB_ARM_ACK)
		dev_warn(master->dev, "GPIO request arbitration timeout\n");

	return 0;
}