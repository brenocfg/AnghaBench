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
struct tiadc_dma {scalar_t__ chan; } ;
struct tiadc_device {scalar_t__ total_ch_enabled; scalar_t__ buffer_en_ch_steps; int /*<<< orphan*/  mfd_tscadc; struct tiadc_dma dma; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int IRQENB_FIFO1OVRRUN ; 
 int IRQENB_FIFO1THRES ; 
 int IRQENB_FIFO1UNDRFLW ; 
 int /*<<< orphan*/  REG_DMAENABLE_CLEAR ; 
 int /*<<< orphan*/  REG_FIFO1 ; 
 int /*<<< orphan*/  REG_FIFO1CNT ; 
 int /*<<< orphan*/  REG_IRQCLR ; 
 int /*<<< orphan*/  am335x_tsc_se_clr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dmaengine_terminate_async (scalar_t__) ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 int tiadc_readl (struct tiadc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiadc_writel (struct tiadc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tiadc_buffer_predisable(struct iio_dev *indio_dev)
{
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	struct tiadc_dma *dma = &adc_dev->dma;
	int fifo1count, i, read;

	tiadc_writel(adc_dev, REG_IRQCLR, (IRQENB_FIFO1THRES |
				IRQENB_FIFO1OVRRUN | IRQENB_FIFO1UNDRFLW));
	am335x_tsc_se_clr(adc_dev->mfd_tscadc, adc_dev->buffer_en_ch_steps);
	adc_dev->buffer_en_ch_steps = 0;
	adc_dev->total_ch_enabled = 0;
	if (dma->chan) {
		tiadc_writel(adc_dev, REG_DMAENABLE_CLEAR, 0x2);
		dmaengine_terminate_async(dma->chan);
	}

	/* Flush FIFO of leftover data in the time it takes to disable adc */
	fifo1count = tiadc_readl(adc_dev, REG_FIFO1CNT);
	for (i = 0; i < fifo1count; i++)
		read = tiadc_readl(adc_dev, REG_FIFO1);

	return 0;
}