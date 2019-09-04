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
struct pm8xxx_xoadc {int /*<<< orphan*/  complete; } ;
struct iio_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct pm8xxx_xoadc* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static irqreturn_t pm8xxx_eoc_irq(int irq, void *d)
{
	struct iio_dev *indio_dev = d;
	struct pm8xxx_xoadc *adc = iio_priv(indio_dev);

	complete(&adc->complete);

	return IRQ_HANDLED;
}