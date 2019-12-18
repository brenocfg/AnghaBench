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
struct xadc {int zynq_intmask; int zynq_masked_alarm; int /*<<< orphan*/  lock; int /*<<< orphan*/  zynq_unmask_work; int /*<<< orphan*/  completion; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int XADC_ZYNQ_INT_ALARM_MASK ; 
 int XADC_ZYNQ_INT_DFIFO_GTH ; 
 int /*<<< orphan*/  XADC_ZYNQ_REG_INTSTS ; 
 int /*<<< orphan*/  XADC_ZYNQ_UNMASK_TIMEOUT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct xadc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xadc_handle_events (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xadc_read_reg (struct xadc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xadc_write_reg (struct xadc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xadc_zynq_transform_alarm (int) ; 
 int /*<<< orphan*/  xadc_zynq_update_intmsk (struct xadc*,int,int) ; 

__attribute__((used)) static irqreturn_t xadc_zynq_interrupt_handler(int irq, void *devid)
{
	struct iio_dev *indio_dev = devid;
	struct xadc *xadc = iio_priv(indio_dev);
	uint32_t status;

	xadc_read_reg(xadc, XADC_ZYNQ_REG_INTSTS, &status);

	status &= ~(xadc->zynq_intmask | xadc->zynq_masked_alarm);

	if (!status)
		return IRQ_NONE;

	spin_lock(&xadc->lock);

	xadc_write_reg(xadc, XADC_ZYNQ_REG_INTSTS, status);

	if (status & XADC_ZYNQ_INT_DFIFO_GTH) {
		xadc_zynq_update_intmsk(xadc, XADC_ZYNQ_INT_DFIFO_GTH,
			XADC_ZYNQ_INT_DFIFO_GTH);
		complete(&xadc->completion);
	}

	status &= XADC_ZYNQ_INT_ALARM_MASK;
	if (status) {
		xadc->zynq_masked_alarm |= status;
		/*
		 * mask the current event interrupt,
		 * unmask it when the interrupt is no more active.
		 */
		xadc_zynq_update_intmsk(xadc, 0, 0);

		xadc_handle_events(indio_dev,
				xadc_zynq_transform_alarm(status));

		/* unmask the required interrupts in timer. */
		schedule_delayed_work(&xadc->zynq_unmask_work,
				msecs_to_jiffies(XADC_ZYNQ_UNMASK_TIMEOUT));
	}
	spin_unlock(&xadc->lock);

	return IRQ_HANDLED;
}