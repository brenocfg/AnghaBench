#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_queue_manager {TYPE_2__* dev; } ;
struct TYPE_3__ {int num_pipe_per_mec; int num_queue_per_pipe; int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_4__ {TYPE_1__ shared_resources; } ;

/* Variables and functions */
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_pipe_enabled(struct device_queue_manager *dqm, int mec, int pipe)
{
	int i;
	int pipe_offset = mec * dqm->dev->shared_resources.num_pipe_per_mec
		+ pipe * dqm->dev->shared_resources.num_queue_per_pipe;

	/* queue is available for KFD usage if bit is 1 */
	for (i = 0; i <  dqm->dev->shared_resources.num_queue_per_pipe; ++i)
		if (test_bit(pipe_offset + i,
			      dqm->dev->shared_resources.queue_bitmap))
			return true;
	return false;
}