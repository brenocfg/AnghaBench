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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMC5843_MODE_CONVERSION_CONTINUOUS ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int hmc5843_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_priv (int /*<<< orphan*/ ) ; 

int hmc5843_common_resume(struct device *dev)
{
	return hmc5843_set_mode(iio_priv(dev_get_drvdata(dev)),
		HMC5843_MODE_CONVERSION_CONTINUOUS);
}