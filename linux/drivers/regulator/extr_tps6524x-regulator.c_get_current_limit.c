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
struct tps6524x {int dummy; } ;
struct supply_info {int n_ilimsels; int* ilimsels; int /*<<< orphan*/  ilimsel; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 struct tps6524x* rdev_get_drvdata (struct regulator_dev*) ; 
 size_t rdev_get_id (struct regulator_dev*) ; 
 int read_field (struct tps6524x*,int /*<<< orphan*/ *) ; 
 struct supply_info* supply_info ; 

__attribute__((used)) static int get_current_limit(struct regulator_dev *rdev)
{
	const struct supply_info *info;
	struct tps6524x *hw;
	int ret;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	if (info->n_ilimsels == 1)
		return info->ilimsels[0];

	ret = read_field(hw, &info->ilimsel);
	if (ret < 0)
		return ret;
	if (WARN_ON(ret >= info->n_ilimsels))
		return -EIO;

	return info->ilimsels[ret];
}