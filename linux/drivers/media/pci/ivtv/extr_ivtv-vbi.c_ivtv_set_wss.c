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
struct v4l2_sliced_vbi_data {int line; int* data; scalar_t__ field; int /*<<< orphan*/  id; } ;
struct ivtv {int v4l2_cap; int std_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_HW_SAA7127 ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_SLICED_WSS_625 ; 
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  ivtv_call_hw (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_sliced_vbi_data*) ; 
 int /*<<< orphan*/  s_vbi_data ; 
 int /*<<< orphan*/  vbi ; 

__attribute__((used)) static void ivtv_set_wss(struct ivtv *itv, int enabled, int mode)
{
	struct v4l2_sliced_vbi_data data;

	if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return;
	/* When using a 50 Hz system, always turn on the
	   wide screen signal with 4x3 ratio as the default.
	   Turning this signal on and off can confuse certain
	   TVs. As far as I can tell there is no reason not to
	   transmit this signal. */
	if ((itv->std_out & V4L2_STD_625_50) && !enabled) {
		enabled = 1;
		mode = 0x08;  /* 4x3 full format */
	}
	data.id = V4L2_SLICED_WSS_625;
	data.field = 0;
	data.line = enabled ? 23 : 0;
	data.data[0] = mode & 0xff;
	data.data[1] = (mode >> 8) & 0xff;
	ivtv_call_hw(itv, IVTV_HW_SAA7127, vbi, s_vbi_data, &data);
}