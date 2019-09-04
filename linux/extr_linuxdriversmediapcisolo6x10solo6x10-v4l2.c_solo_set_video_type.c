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
struct solo_dev {int nr_chans; int /*<<< orphan*/  cur_disp_ch; TYPE_1__** v4l2_enc; int /*<<< orphan*/  video_type; int /*<<< orphan*/  vidq; } ;
struct TYPE_2__ {int /*<<< orphan*/  vidq; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SOLO_VO_FMT_TYPE_NTSC ; 
 int /*<<< orphan*/  SOLO_VO_FMT_TYPE_PAL ; 
 int /*<<< orphan*/  solo_disp_init (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_enc_init (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_tw28_init (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_update_mode (TYPE_1__*) ; 
 int solo_v4l2_set_ch (struct solo_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 

int solo_set_video_type(struct solo_dev *solo_dev, bool is_50hz)
{
	int i;

	/* Make sure all video nodes are idle */
	if (vb2_is_busy(&solo_dev->vidq))
		return -EBUSY;
	for (i = 0; i < solo_dev->nr_chans; i++)
		if (vb2_is_busy(&solo_dev->v4l2_enc[i]->vidq))
			return -EBUSY;
	solo_dev->video_type = is_50hz ? SOLO_VO_FMT_TYPE_PAL :
					 SOLO_VO_FMT_TYPE_NTSC;
	/* Reconfigure for the new standard */
	solo_disp_init(solo_dev);
	solo_enc_init(solo_dev);
	solo_tw28_init(solo_dev);
	for (i = 0; i < solo_dev->nr_chans; i++)
		solo_update_mode(solo_dev->v4l2_enc[i]);
	return solo_v4l2_set_ch(solo_dev, solo_dev->cur_disp_ch);
}