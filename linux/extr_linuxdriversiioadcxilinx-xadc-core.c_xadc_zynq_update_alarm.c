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
 unsigned int XADC_ZYNQ_INT_ALARM_MASK ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_INTSTS ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xadc_read_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xadc_zynq_update_intmsk (struct xadc*,unsigned int,unsigned int) ; 

__attribute__((used)) static void xadc_zynq_update_alarm(struct xadc *xadc, unsigned int alarm)
{
	unsigned long flags;
	uint32_t status;

	/* Move OT to bit 7 */
	alarm = ((alarm & 0x08) << 4) | ((alarm & 0xf0) >> 1) | (alarm & 0x07);

	spin_lock_irqsave(&xadc->lock, flags);

	/* Clear previous interrupts if any. */
	xadc_read_reg(xadc, XADC_ZYNQ_REG_INTSTS, &status);
	xadc_write_reg(xadc, XADC_ZYNQ_REG_INTSTS, status & alarm);

	xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_ALARM_MASK,
		~alarm & XADC_ZYNQ_INT_ALARM_MASK);

	spin_unlock_irqrestore(&xadc->lock, flags);
}