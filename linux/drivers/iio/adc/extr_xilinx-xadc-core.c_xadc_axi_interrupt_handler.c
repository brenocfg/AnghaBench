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
typedef  int uint32_t ;
struct xadc {scalar_t__ trigger; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int XADC_AXI_INT_ALARM_MASK ; 
 int XADC_AXI_INT_EOS ; 
 int /*<<< orphan*/  XADC_AXI_REG_IPIER ; 
 int /*<<< orphan*/  XADC_AXI_REG_IPISR ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (scalar_t__) ; 
 int /*<<< orphan*/  xadc_handle_events (struct iio_dev*,unsigned int) ; 
 int /*<<< orphan*/  xadc_read_reg (struct xadc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t xadc_axi_interrupt_handler(int irq, void *devid)
{
	struct iio_dev *indio_dev = devid;
	struct xadc *xadc = iio_priv(indio_dev);
	uint32_t status, mask;
	unsigned int events;

	xadc_read_reg(xadc, XADC_AXI_REG_IPISR, &status);
	xadc_read_reg(xadc, XADC_AXI_REG_IPIER, &mask);
	status &= mask;

	if (!status)
		return IRQ_NONE;

	if ((status & XADC_AXI_INT_EOS) && xadc->trigger)
		iio_trigger_poll(xadc->trigger);

	if (status & XADC_AXI_INT_ALARM_MASK) {
		/*
		 * The order of the bits in the AXI-XADC status register does
		 * not match the order of the bits in the XADC alarm enable
		 * register. xadc_handle_events() expects the events to be in
		 * the same order as the XADC alarm enable register.
		 */
		events = (status & 0x000e) >> 1;
		events |= (status & 0x0001) << 3;
		events |= (status & 0x3c00) >> 6;
		xadc_handle_events(indio_dev, events);
	}

	xadc_write_reg(xadc, XADC_AXI_REG_IPISR, status);

	return IRQ_HANDLED;
}