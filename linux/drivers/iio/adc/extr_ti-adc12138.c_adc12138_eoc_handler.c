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
struct iio_dev {int dummy; } ;
struct adc12138 {int /*<<< orphan*/  complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct adc12138* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t adc12138_eoc_handler(int irq, void *p)
{
	struct iio_dev *indio_dev = p;
	struct adc12138 *adc = iio_priv(indio_dev);

	complete(&adc->complete);

	return IRQ_HANDLED;
}