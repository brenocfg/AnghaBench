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
struct gendisk {int /*<<< orphan*/  bb; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  badblocks_show (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct gendisk* dev_to_disk (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t disk_badblocks_show(struct device *dev,
					struct device_attribute *attr,
					char *page)
{
	struct gendisk *disk = dev_to_disk(dev);

	if (!disk->bb)
		return sprintf(page, "\n");

	return badblocks_show(disk->bb, page, 0);
}