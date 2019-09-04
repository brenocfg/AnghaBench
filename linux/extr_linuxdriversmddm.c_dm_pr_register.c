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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct dm_pr {int fail_early; scalar_t__ flags; scalar_t__ new_key; scalar_t__ old_key; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dm_pr_register ; 
 int dm_call_pr (struct block_device*,int /*<<< orphan*/ ,struct dm_pr*) ; 

__attribute__((used)) static int dm_pr_register(struct block_device *bdev, u64 old_key, u64 new_key,
			  u32 flags)
{
	struct dm_pr pr = {
		.old_key	= old_key,
		.new_key	= new_key,
		.flags		= flags,
		.fail_early	= true,
	};
	int ret;

	ret = dm_call_pr(bdev, __dm_pr_register, &pr);
	if (ret && new_key) {
		/* unregister all paths if we failed to register any path */
		pr.old_key = new_key;
		pr.new_key = 0;
		pr.flags = 0;
		pr.fail_early = false;
		dm_call_pr(bdev, __dm_pr_register, &pr);
	}

	return ret;
}