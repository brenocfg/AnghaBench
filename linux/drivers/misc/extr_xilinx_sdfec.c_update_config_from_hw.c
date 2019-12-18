#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int enable_isr; int enable_ecc_isr; } ;
struct TYPE_4__ {int order; TYPE_1__ irq; int /*<<< orphan*/  code_wr_protect; int /*<<< orphan*/  bypass; } ;
struct xsdfec_dev {int /*<<< orphan*/  state; TYPE_2__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSDFEC_AXIS_ENABLE_ADDR ; 
 int XSDFEC_AXIS_IN_ENABLE_MASK ; 
 int /*<<< orphan*/  XSDFEC_BYPASS_ADDR ; 
 int /*<<< orphan*/  XSDFEC_CODE_WR_PROTECT_ADDR ; 
 int /*<<< orphan*/  XSDFEC_ECC_IMR_ADDR ; 
 int XSDFEC_ECC_ISR_MASK ; 
 int /*<<< orphan*/  XSDFEC_IMR_ADDR ; 
 int XSDFEC_ISR_MASK ; 
 int /*<<< orphan*/  XSDFEC_ORDER_ADDR ; 
 int /*<<< orphan*/  XSDFEC_STARTED ; 
 int /*<<< orphan*/  XSDFEC_STOPPED ; 
 int /*<<< orphan*/  update_bool_config_from_reg (struct xsdfec_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xsdfec_regread (struct xsdfec_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_config_from_hw(struct xsdfec_dev *xsdfec)
{
	u32 reg_value;
	bool sdfec_started;

	/* Update the Order */
	reg_value = xsdfec_regread(xsdfec, XSDFEC_ORDER_ADDR);
	xsdfec->config.order = reg_value;

	update_bool_config_from_reg(xsdfec, XSDFEC_BYPASS_ADDR,
				    0, /* Bit Number, maybe change to mask */
				    &xsdfec->config.bypass);

	update_bool_config_from_reg(xsdfec, XSDFEC_CODE_WR_PROTECT_ADDR,
				    0, /* Bit Number */
				    &xsdfec->config.code_wr_protect);

	reg_value = xsdfec_regread(xsdfec, XSDFEC_IMR_ADDR);
	xsdfec->config.irq.enable_isr = (reg_value & XSDFEC_ISR_MASK) > 0;

	reg_value = xsdfec_regread(xsdfec, XSDFEC_ECC_IMR_ADDR);
	xsdfec->config.irq.enable_ecc_isr =
		(reg_value & XSDFEC_ECC_ISR_MASK) > 0;

	reg_value = xsdfec_regread(xsdfec, XSDFEC_AXIS_ENABLE_ADDR);
	sdfec_started = (reg_value & XSDFEC_AXIS_IN_ENABLE_MASK) > 0;
	if (sdfec_started)
		xsdfec->state = XSDFEC_STARTED;
	else
		xsdfec->state = XSDFEC_STOPPED;
}