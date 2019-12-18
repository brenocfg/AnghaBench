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
struct TYPE_2__ {int /*<<< orphan*/ * virt; int /*<<< orphan*/  size; } ;
struct uflash_dev {TYPE_1__ map; scalar_t__ mtd; } ;
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct uflash_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct uflash_dev*) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtd_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uflash_remove(struct platform_device *op)
{
	struct uflash_dev *up = dev_get_drvdata(&op->dev);

	if (up->mtd) {
		mtd_device_unregister(up->mtd);
		map_destroy(up->mtd);
	}
	if (up->map.virt) {
		of_iounmap(&op->resource[0], up->map.virt, up->map.size);
		up->map.virt = NULL;
	}

	kfree(up);

	return 0;
}