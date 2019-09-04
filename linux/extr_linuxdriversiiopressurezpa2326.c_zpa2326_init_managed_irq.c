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
struct zpa2326_private {int irq; int /*<<< orphan*/  data_ready; } ;
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpa2326_handle_irq ; 
 int /*<<< orphan*/  zpa2326_handle_threaded_irq ; 

__attribute__((used)) static int zpa2326_init_managed_irq(struct device          *parent,
				    struct iio_dev         *indio_dev,
				    struct zpa2326_private *private,
				    int                     irq)
{
	int err;

	private->irq = irq;

	if (irq <= 0) {
		/*
		 * Platform declared no interrupt line: device will be polled
		 * for data availability.
		 */
		dev_info(parent, "no interrupt found, running in polling mode");
		return 0;
	}

	init_completion(&private->data_ready);

	/* Request handler to be scheduled into threaded interrupt context. */
	err = devm_request_threaded_irq(parent, irq, zpa2326_handle_irq,
					zpa2326_handle_threaded_irq,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					dev_name(parent), indio_dev);
	if (err) {
		dev_err(parent, "failed to request interrupt %d (%d)", irq,
			err);
		return err;
	}

	dev_info(parent, "using interrupt %d", irq);

	return 0;
}