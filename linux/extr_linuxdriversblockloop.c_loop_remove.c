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
struct loop_device {int /*<<< orphan*/  lo_disk; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  lo_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct loop_device*) ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void loop_remove(struct loop_device *lo)
{
	del_gendisk(lo->lo_disk);
	blk_cleanup_queue(lo->lo_queue);
	blk_mq_free_tag_set(&lo->tag_set);
	put_disk(lo->lo_disk);
	kfree(lo);
}