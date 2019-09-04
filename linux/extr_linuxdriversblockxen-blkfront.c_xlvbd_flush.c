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
struct blkfront_info {scalar_t__ max_indirect_segments; scalar_t__ feature_persistent; TYPE_1__* gd; scalar_t__ feature_fua; scalar_t__ feature_flush; int /*<<< orphan*/  rq; } ;
struct TYPE_2__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_queue_write_cache (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  flush_info (struct blkfront_info*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static void xlvbd_flush(struct blkfront_info *info)
{
	blk_queue_write_cache(info->rq, info->feature_flush ? true : false,
			      info->feature_fua ? true : false);
	pr_info("blkfront: %s: %s %s %s %s %s\n",
		info->gd->disk_name, flush_info(info),
		"persistent grants:", info->feature_persistent ?
		"enabled;" : "disabled;", "indirect descriptors:",
		info->max_indirect_segments ? "enabled;" : "disabled;");
}