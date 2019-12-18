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
struct mapped_device {scalar_t__ tag_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_tag_set (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

void dm_mq_cleanup_mapped_device(struct mapped_device *md)
{
	if (md->tag_set) {
		blk_mq_free_tag_set(md->tag_set);
		kfree(md->tag_set);
	}
}