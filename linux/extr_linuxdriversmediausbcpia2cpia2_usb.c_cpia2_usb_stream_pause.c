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
struct camera_data {scalar_t__ streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBIF_CMDONLY ; 
 int /*<<< orphan*/  free_sbufs (struct camera_data*) ; 
 int set_alternate (struct camera_data*,int /*<<< orphan*/ ) ; 

int cpia2_usb_stream_pause(struct camera_data *cam)
{
	int ret = 0;
	if(cam->streaming) {
		free_sbufs(cam);
		ret = set_alternate(cam, USBIF_CMDONLY);
	}
	return ret;
}