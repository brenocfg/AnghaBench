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
struct camera_data {int frame_size; int num_frames; int /*<<< orphan*/ * frame_buffer; int /*<<< orphan*/ * buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ *,int) ; 

void cpia2_free_buffers(struct camera_data *cam)
{
	if(cam->buffers) {
		kfree(cam->buffers);
		cam->buffers = NULL;
	}
	if(cam->frame_buffer) {
		rvfree(cam->frame_buffer, cam->frame_size*cam->num_frames);
		cam->frame_buffer = NULL;
	}
}