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
struct vf610_adc {scalar_t__ regs; } ;
struct iio_dev {int /*<<< orphan*/  masklength; int /*<<< orphan*/  active_scan_mask; } ;

/* Variables and functions */
 int VF610_ADC_ADCHC (unsigned int) ; 
 int VF610_ADC_ADCON ; 
 int VF610_ADC_AIEN ; 
 scalar_t__ VF610_REG_ADC_GC ; 
 scalar_t__ VF610_REG_ADC_HC0 ; 
 unsigned int find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vf610_adc* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int vf610_adc_buffer_postenable(struct iio_dev *indio_dev)
{
	struct vf610_adc *info = iio_priv(indio_dev);
	unsigned int channel;
	int ret;
	int val;

	ret = iio_triggered_buffer_postenable(indio_dev);
	if (ret)
		return ret;

	val = readl(info->regs + VF610_REG_ADC_GC);
	val |= VF610_ADC_ADCON;
	writel(val, info->regs + VF610_REG_ADC_GC);

	channel = find_first_bit(indio_dev->active_scan_mask,
						indio_dev->masklength);

	val = VF610_ADC_ADCHC(channel);
	val |= VF610_ADC_AIEN;

	writel(val, info->regs + VF610_REG_ADC_HC0);

	return 0;
}