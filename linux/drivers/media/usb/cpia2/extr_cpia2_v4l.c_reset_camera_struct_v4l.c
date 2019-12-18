#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  flicker_mode_req; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_2__ camera_state; TYPE_1__ flicker_control; TYPE_3__ roi; } ;
struct camera_data {int /*<<< orphan*/  pixelformat; TYPE_4__ params; int /*<<< orphan*/  num_frames; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_JPEG ; 
 int /*<<< orphan*/  alternate ; 
 int /*<<< orphan*/  buffer_size ; 
 int /*<<< orphan*/  flicker_mode ; 
 int /*<<< orphan*/  num_buffers ; 

__attribute__((used)) static void reset_camera_struct_v4l(struct camera_data *cam)
{
	cam->width = cam->params.roi.width;
	cam->height = cam->params.roi.height;

	cam->frame_size = buffer_size;
	cam->num_frames = num_buffers;

	/* Flicker modes */
	cam->params.flicker_control.flicker_mode_req = flicker_mode;

	/* stream modes */
	cam->params.camera_state.stream_mode = alternate;

	cam->pixelformat = V4L2_PIX_FMT_JPEG;
}