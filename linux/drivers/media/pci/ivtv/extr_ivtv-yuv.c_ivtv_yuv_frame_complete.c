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
struct TYPE_2__ {int draw_frame; int /*<<< orphan*/  next_fill_frame; } ;
struct ivtv {TYPE_1__ yuv_info; } ;

/* Variables and functions */
 int IVTV_YUV_BUFFERS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

void ivtv_yuv_frame_complete(struct ivtv *itv)
{
	atomic_set(&itv->yuv_info.next_fill_frame,
			(itv->yuv_info.draw_frame + 1) % IVTV_YUV_BUFFERS);
}