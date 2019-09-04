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
struct iio_trigger {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_iio_trigger_match ; 
 int /*<<< orphan*/  devm_iio_trigger_release ; 
 int devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iio_trigger*) ; 

void devm_iio_trigger_free(struct device *dev, struct iio_trigger *iio_trig)
{
	int rc;

	rc = devres_release(dev, devm_iio_trigger_release,
			    devm_iio_trigger_match, iio_trig);
	WARN_ON(rc);
}