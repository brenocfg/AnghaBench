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
struct regulator_dev {int dummy; } ;
struct max8952_data {unsigned int vid0; unsigned int vid1; int /*<<< orphan*/  vid1_gpiod; int /*<<< orphan*/  vid0_gpiod; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,unsigned int) ; 
 struct max8952_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max8952_set_voltage_sel(struct regulator_dev *rdev,
				   unsigned selector)
{
	struct max8952_data *max8952 = rdev_get_drvdata(rdev);

	if (!max8952->vid0_gpiod || !max8952->vid1_gpiod) {
		/* DVS not supported */
		return -EPERM;
	}

	max8952->vid0 = selector & 0x1;
	max8952->vid1 = (selector >> 1) & 0x1;
	gpiod_set_value(max8952->vid0_gpiod, max8952->vid0);
	gpiod_set_value(max8952->vid1_gpiod, max8952->vid1);

	return 0;
}