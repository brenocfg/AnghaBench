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
struct platram_info {scalar_t__ mtd; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATRAM_RO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct platram_info*) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mtd_device_unregister (scalar_t__) ; 
 int /*<<< orphan*/  platram_setrw (struct platram_info*,int /*<<< orphan*/ ) ; 
 struct platram_info* to_platram_info (struct platform_device*) ; 

__attribute__((used)) static int platram_remove(struct platform_device *pdev)
{
	struct platram_info *info = to_platram_info(pdev);

	dev_dbg(&pdev->dev, "removing device\n");

	if (info == NULL)
		return 0;

	if (info->mtd) {
		mtd_device_unregister(info->mtd);
		map_destroy(info->mtd);
	}

	/* ensure ram is left read-only */

	platram_setrw(info, PLATRAM_RO);

	kfree(info);

	return 0;
}