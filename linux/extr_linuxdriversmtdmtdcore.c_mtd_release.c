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
struct mtd_info {int /*<<< orphan*/  index; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 scalar_t__ MTD_DEVT (int /*<<< orphan*/ ) ; 
 struct mtd_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mtd_class ; 

__attribute__((used)) static void mtd_release(struct device *dev)
{
	struct mtd_info *mtd = dev_get_drvdata(dev);
	dev_t index = MTD_DEVT(mtd->index);

	/* remove /dev/mtdXro node */
	device_destroy(&mtd_class, index + 1);
}