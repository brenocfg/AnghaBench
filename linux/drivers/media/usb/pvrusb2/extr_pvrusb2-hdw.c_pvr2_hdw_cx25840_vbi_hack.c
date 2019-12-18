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
struct TYPE_4__ {void*** service_lines; } ;
struct TYPE_3__ {TYPE_2__ sliced; } ;
struct v4l2_format {TYPE_1__ fmt; int /*<<< orphan*/  type; } ;
struct pvr2_hdw {scalar_t__ decoder_client_id; int /*<<< orphan*/  v4l2_dev; } ;
typedef  int /*<<< orphan*/  fmt ;

/* Variables and functions */
 scalar_t__ PVR2_CLIENT_ID_CX25840 ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ; 
 void* V4L2_SLICED_CAPTION_525 ; 
 int /*<<< orphan*/  memset (struct v4l2_format*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  s_sliced_fmt ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vbi ; 

__attribute__((used)) static void pvr2_hdw_cx25840_vbi_hack(struct pvr2_hdw *hdw)
{
	/*
	  Mike Isely <isely@pobox.com> 19-Nov-2006 - This bit of nuttiness
	  for cx25840 causes that module to correctly set up its video
	  scaling.  This is really a problem in the cx25840 module itself,
	  but we work around it here.  The problem has not been seen in
	  ivtv because there VBI is supported and set up.  We don't do VBI
	  here (at least not yet) and thus we never attempted to even set
	  it up.
	*/
	struct v4l2_format fmt;
	if (hdw->decoder_client_id != PVR2_CLIENT_ID_CX25840) {
		/* We're not using a cx25840 so don't enable the hack */
		return;
	}

	pvr2_trace(PVR2_TRACE_INIT,
		   "Module ID %u: Executing cx25840 VBI hack",
		   hdw->decoder_client_id);
	memset(&fmt, 0, sizeof(fmt));
	fmt.type = V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	fmt.fmt.sliced.service_lines[0][21] = V4L2_SLICED_CAPTION_525;
	fmt.fmt.sliced.service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	v4l2_device_call_all(&hdw->v4l2_dev, hdw->decoder_client_id,
			     vbi, s_sliced_fmt, &fmt.fmt.sliced);
}