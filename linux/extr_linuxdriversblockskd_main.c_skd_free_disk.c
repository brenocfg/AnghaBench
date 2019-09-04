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
struct TYPE_2__ {scalar_t__ tags; } ;
struct skd_device {struct gendisk* disk; TYPE_1__ tag_set; int /*<<< orphan*/ * queue; } ;
struct gendisk {int flags; int /*<<< orphan*/ * queue; } ;

/* Variables and functions */
 int GENHD_FL_UP ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_1__*) ; 
 int /*<<< orphan*/  del_gendisk (struct gendisk*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 

__attribute__((used)) static void skd_free_disk(struct skd_device *skdev)
{
	struct gendisk *disk = skdev->disk;

	if (disk && (disk->flags & GENHD_FL_UP))
		del_gendisk(disk);

	if (skdev->queue) {
		blk_cleanup_queue(skdev->queue);
		skdev->queue = NULL;
		if (disk)
			disk->queue = NULL;
	}

	if (skdev->tag_set.tags)
		blk_mq_free_tag_set(&skdev->tag_set);

	put_disk(disk);
	skdev->disk = NULL;
}