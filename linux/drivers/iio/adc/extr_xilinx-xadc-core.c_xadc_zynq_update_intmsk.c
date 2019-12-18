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
struct xadc {unsigned int zynq_intmask; int zynq_masked_alarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  XADC_ZYNQ_REG_INTMSK ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xadc_zynq_update_intmsk(struct xadc *xadc, unsigned int mask,
	unsigned int val)
{
	xadc->zynq_intmask &= ~mask;
	xadc->zynq_intmask |= val;

	xadc_write_reg(xadc, XADC_ZYNQ_REG_INTMSK,
		xadc->zynq_intmask | xadc->zynq_masked_alarm);
}