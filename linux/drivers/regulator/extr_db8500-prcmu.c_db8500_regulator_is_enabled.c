#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dbx500_regulator_info {int is_enabled; TYPE_1__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct dbx500_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int db8500_regulator_is_enabled(struct regulator_dev *rdev)
{
	struct dbx500_regulator_info *info = rdev_get_drvdata(rdev);

	if (info == NULL)
		return -EINVAL;

	dev_vdbg(rdev_get_dev(rdev), "regulator-%s-is_enabled (is_enabled):"
		" %i\n", info->desc.name, info->is_enabled);

	return info->is_enabled;
}