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
struct block_device {int /*<<< orphan*/  bd_dev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct block_device*) ; 
 int /*<<< orphan*/  bdput (struct block_device*) ; 
 struct block_device* lookup_bdev (char const*) ; 
 int /*<<< orphan*/  name_to_dev_t (char const*) ; 

dev_t dm_get_dev_t(const char *path)
{
	dev_t dev;
	struct block_device *bdev;

	bdev = lookup_bdev(path);
	if (IS_ERR(bdev))
		dev = name_to_dev_t(path);
	else {
		dev = bdev->bd_dev;
		bdput(bdev);
	}

	return dev;
}