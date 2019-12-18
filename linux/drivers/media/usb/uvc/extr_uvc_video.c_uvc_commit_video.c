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
struct uvc_streaming_control {int dummy; } ;
struct uvc_streaming {int dummy; } ;

/* Variables and functions */
 int uvc_set_video_ctrl (struct uvc_streaming*,struct uvc_streaming_control*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvc_commit_video(struct uvc_streaming *stream,
			    struct uvc_streaming_control *probe)
{
	return uvc_set_video_ctrl(stream, probe, 0);
}