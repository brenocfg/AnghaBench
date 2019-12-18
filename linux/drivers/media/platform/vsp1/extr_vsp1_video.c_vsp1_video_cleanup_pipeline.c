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
struct vsp1_pipeline {int configured; int /*<<< orphan*/ * part_table; int /*<<< orphan*/ * stream_config; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_dl_body_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vsp1_video_cleanup_pipeline(struct vsp1_pipeline *pipe)
{
	lockdep_assert_held(&pipe->lock);

	/* Release any cached configuration from our output video. */
	vsp1_dl_body_put(pipe->stream_config);
	pipe->stream_config = NULL;
	pipe->configured = false;

	/* Release our partition table allocation. */
	kfree(pipe->part_table);
	pipe->part_table = NULL;
}