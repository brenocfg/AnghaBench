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
typedef  int u8 ;
struct regulator_dev {int dummy; } ;
struct max8952_data {scalar_t__ vid1; scalar_t__ vid0; } ;

/* Variables and functions */
 struct max8952_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max8952_get_voltage_sel(struct regulator_dev *rdev)
{
	struct max8952_data *max8952 = rdev_get_drvdata(rdev);
	u8 vid = 0;

	if (max8952->vid0)
		vid += 1;
	if (max8952->vid1)
		vid += 2;

	return vid;
}