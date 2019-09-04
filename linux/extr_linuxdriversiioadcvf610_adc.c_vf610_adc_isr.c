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
struct vf610_adc {int /*<<< orphan*/  completion; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  value; scalar_t__ regs; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int VF610_ADC_HS_COCO0 ; 
 scalar_t__ VF610_REG_ADC_HS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct vf610_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  vf610_adc_read_data (struct vf610_adc*) ; 

__attribute__((used)) static irqreturn_t vf610_adc_isr(int irq, void *dev_id)
{
	struct iio_dev *indio_dev = dev_id;
	struct vf610_adc *info = iio_priv(indio_dev);
	int coco;

	coco = readl(info->regs + VF610_REG_ADC_HS);
	if (coco & VF610_ADC_HS_COCO0) {
		info->value = vf610_adc_read_data(info);
		if (iio_buffer_enabled(indio_dev)) {
			info->buffer[0] = info->value;
			iio_push_to_buffers_with_timestamp(indio_dev,
					info->buffer,
					iio_get_time_ns(indio_dev));
			iio_trigger_notify_done(indio_dev->trig);
		} else
			complete(&info->completion);
	}

	return IRQ_HANDLED;
}