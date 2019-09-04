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
typedef  unsigned int uint32_t ;
struct xadc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int XADC_AXI_INT_ALARM_MASK ; 
 int /*<<< orphan*/  XADC_AXI_REG_IPIER ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xadc_read_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void xadc_axi_update_alarm(struct xadc *xadc, unsigned int alarm)
{
	uint32_t val;
	unsigned long flags;

	/*
	 * The order of the bits in the AXI-XADC status register does not match
	 * the order of the bits in the XADC alarm enable register. We get
	 * passed the alarm mask in the same order as in the XADC alarm enable
	 * register.
	 */
	alarm = ((alarm & 0x07) << 1) | ((alarm & 0x08) >> 3) |
			((alarm & 0xf0) << 6);

	spin_lock_irqsave(&xadc->lock, flags);
	xadc_read_reg(xadc, XADC_AXI_REG_IPIER, &val);
	val &= ~XADC_AXI_INT_ALARM_MASK;
	val |= alarm;
	xadc_write_reg(xadc, XADC_AXI_REG_IPIER, val);
	spin_unlock_irqrestore(&xadc->lock, flags);
}