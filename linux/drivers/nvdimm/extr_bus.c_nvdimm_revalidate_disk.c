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
struct nd_region {int ro; int /*<<< orphan*/  dev; } ;
struct gendisk {int /*<<< orphan*/  disk_name; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 TYPE_1__* disk_to_dev (struct gendisk*) ; 
 int get_disk_ro (struct gendisk*) ; 
 int /*<<< orphan*/  set_disk_ro (struct gendisk*,int) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

int nvdimm_revalidate_disk(struct gendisk *disk)
{
	struct device *dev = disk_to_dev(disk)->parent;
	struct nd_region *nd_region = to_nd_region(dev->parent);
	int disk_ro = get_disk_ro(disk);

	/*
	 * Upgrade to read-only if the region is read-only preserve as
	 * read-only if the disk is already read-only.
	 */
	if (disk_ro || nd_region->ro == disk_ro)
		return 0;

	dev_info(dev, "%s read-only, marking %s read-only\n",
			dev_name(&nd_region->dev), disk->disk_name);
	set_disk_ro(disk, 1);

	return 0;

}