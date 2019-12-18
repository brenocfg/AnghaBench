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
struct TYPE_2__ {int /*<<< orphan*/  frames; } ;
struct mcam_camera {int next_buf; scalar_t__ state; int /*<<< orphan*/  (* frame_complete ) (struct mcam_camera*,int) ;TYPE_1__ frame_state; int /*<<< orphan*/  sequence; scalar_t__* buf_seq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CF_DMA_ACTIVE ; 
 scalar_t__ S_STREAMING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mcam_camera*,int) ; 

__attribute__((used)) static void mcam_frame_complete(struct mcam_camera *cam, int frame)
{
	/*
	 * Basic frame housekeeping.
	 */
	set_bit(frame, &cam->flags);
	clear_bit(CF_DMA_ACTIVE, &cam->flags);
	cam->next_buf = frame;
	cam->buf_seq[frame] = cam->sequence++;
	cam->frame_state.frames++;
	/*
	 * "This should never happen"
	 */
	if (cam->state != S_STREAMING)
		return;
	/*
	 * Process the frame and set up the next one.
	 */
	cam->frame_complete(cam, frame);
}