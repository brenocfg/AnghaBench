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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct tiadc_device {int* data; } ;
struct iio_dev {int scan_bytes; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FIFOREAD_DATA_MASK ; 
 int /*<<< orphan*/  IRQENB_FIFO1THRES ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_FIFO1 ; 
 int /*<<< orphan*/  REG_FIFO1CNT ; 
 int /*<<< orphan*/  REG_IRQENABLE ; 
 int /*<<< orphan*/  REG_IRQSTATUS ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int tiadc_readl (struct tiadc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiadc_writel (struct tiadc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tiadc_worker_h(int irq, void *private)
{
	struct iio_dev *indio_dev = private;
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	int i, k, fifo1count, read;
	u16 *data = adc_dev->data;

	fifo1count = tiadc_readl(adc_dev, REG_FIFO1CNT);
	for (k = 0; k < fifo1count; k = k + i) {
		for (i = 0; i < (indio_dev->scan_bytes)/2; i++) {
			read = tiadc_readl(adc_dev, REG_FIFO1);
			data[i] = read & FIFOREAD_DATA_MASK;
		}
		iio_push_to_buffers(indio_dev, (u8 *) data);
	}

	tiadc_writel(adc_dev, REG_IRQSTATUS, IRQENB_FIFO1THRES);
	tiadc_writel(adc_dev, REG_IRQENABLE, IRQENB_FIFO1THRES);

	return IRQ_HANDLED;
}