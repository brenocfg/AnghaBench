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
typedef  int u8 ;
struct uvc_streaming {int last_fid; } ;
struct uvc_buffer {int dummy; } ;

/* Variables and functions */
 int UVC_STREAM_EOF ; 
 int UVC_STREAM_EOH ; 
 int UVC_STREAM_FID ; 

__attribute__((used)) static int uvc_video_encode_header(struct uvc_streaming *stream,
		struct uvc_buffer *buf, u8 *data, int len)
{
	data[0] = 2;	/* Header length */
	data[1] = UVC_STREAM_EOH | UVC_STREAM_EOF
		| (stream->last_fid & UVC_STREAM_FID);
	return 2;
}