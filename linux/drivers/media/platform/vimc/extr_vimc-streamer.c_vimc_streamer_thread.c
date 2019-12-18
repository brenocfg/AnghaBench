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
typedef  int /*<<< orphan*/  u8 ;
struct vimc_stream {int pipe_size; TYPE_1__** ved_pipeline; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* process_frame ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static int vimc_streamer_thread(void *data)
{
	struct vimc_stream *stream = data;
	u8 *frame = NULL;
	int i;

	set_freezable();

	for (;;) {
		try_to_freeze();
		if (kthread_should_stop())
			break;

		for (i = stream->pipe_size - 1; i >= 0; i--) {
			frame = stream->ved_pipeline[i]->process_frame(
					stream->ved_pipeline[i], frame);
			if (!frame || IS_ERR(frame))
				break;
		}
		//wait for 60hz
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(HZ / 60);
	}

	return 0;
}