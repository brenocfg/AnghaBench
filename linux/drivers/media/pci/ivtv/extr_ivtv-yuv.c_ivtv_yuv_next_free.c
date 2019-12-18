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
typedef  int u8 ;
struct yuv_playback_info {int max_frames_buffered; int draw_frame; TYPE_1__* new_frame_info; int /*<<< orphan*/  next_dma_frame; int /*<<< orphan*/  next_fill_frame; } ;
struct ivtv {struct yuv_playback_info yuv_info; } ;
struct TYPE_2__ {scalar_t__ update; } ;

/* Variables and functions */
 int IVTV_YUV_BUFFERS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtv_yuv_init (struct ivtv*) ; 

__attribute__((used)) static void ivtv_yuv_next_free(struct ivtv *itv)
{
	int draw, display;
	struct yuv_playback_info *yi = &itv->yuv_info;

	if (atomic_read(&yi->next_dma_frame) == -1)
		ivtv_yuv_init(itv);

	draw = atomic_read(&yi->next_fill_frame);
	display = atomic_read(&yi->next_dma_frame);

	if (display > draw)
		display -= IVTV_YUV_BUFFERS;

	if (draw - display >= yi->max_frames_buffered)
		draw = (u8)(draw - 1) % IVTV_YUV_BUFFERS;
	else
		yi->new_frame_info[draw].update = 0;

	yi->draw_frame = draw;
}