#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int stream_mode; } ;
struct TYPE_6__ {TYPE_2__ camera_state; } ;
struct camera_data {int streaming; int flush; int num_frames; scalar_t__ frame_count; TYPE_3__ params; TYPE_1__* curbuff; int /*<<< orphan*/  workbuff; TYPE_1__* buffers; } ;
struct TYPE_4__ {int /*<<< orphan*/  next; scalar_t__ length; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  ERR (char*,unsigned int,...) ; 
 int /*<<< orphan*/  FRAME_EMPTY ; 
 int /*<<< orphan*/  USBIF_CMDONLY ; 
 int cpia2_usb_change_streaming_alternate (struct camera_data*,unsigned int) ; 
 int cpia2_usb_stream_resume (struct camera_data*) ; 
 int set_alternate (struct camera_data*,int /*<<< orphan*/ ) ; 

int cpia2_usb_stream_start(struct camera_data *cam, unsigned int alternate)
{
	int ret;
	int old_alt;

	if(cam->streaming)
		return 0;

	if (cam->flush) {
		int i;
		DBG("Flushing buffers\n");
		for(i=0; i<cam->num_frames; ++i) {
			cam->buffers[i].status = FRAME_EMPTY;
			cam->buffers[i].length = 0;
		}
		cam->curbuff = &cam->buffers[0];
		cam->workbuff = cam->curbuff->next;
		cam->flush = false;
	}

	old_alt = cam->params.camera_state.stream_mode;
	cam->params.camera_state.stream_mode = 0;
	ret = cpia2_usb_change_streaming_alternate(cam, alternate);
	if (ret < 0) {
		int ret2;
		ERR("cpia2_usb_change_streaming_alternate() = %d!\n", ret);
		cam->params.camera_state.stream_mode = old_alt;
		ret2 = set_alternate(cam, USBIF_CMDONLY);
		if (ret2 < 0) {
			ERR("cpia2_usb_change_streaming_alternate(%d) =%d has already failed. Then tried to call set_alternate(USBIF_CMDONLY) = %d.\n",
			    alternate, ret, ret2);
		}
	} else {
		cam->frame_count = 0;
		cam->streaming = 1;
		ret = cpia2_usb_stream_resume(cam);
	}
	return ret;
}