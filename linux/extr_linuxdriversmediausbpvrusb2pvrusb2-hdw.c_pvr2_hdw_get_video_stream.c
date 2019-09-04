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
struct pvr2_stream {int dummy; } ;
struct pvr2_hdw {struct pvr2_stream* vid_stream; } ;

/* Variables and functions */

struct pvr2_stream *pvr2_hdw_get_video_stream(struct pvr2_hdw *hp)
{
	return hp->vid_stream;
}