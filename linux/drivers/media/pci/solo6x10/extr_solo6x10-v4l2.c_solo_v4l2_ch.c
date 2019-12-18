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
typedef  scalar_t__ u8 ;
struct solo_dev {scalar_t__ nr_chans; scalar_t__ nr_ext; int /*<<< orphan*/  video_hsize; } ;

/* Variables and functions */
 int EINVAL ; 
 int solo_v4l2_ch_ext_16up (struct solo_dev*,int) ; 
 int solo_v4l2_ch_ext_4up (struct solo_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  solo_vlines (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_win_setup (struct solo_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int solo_v4l2_ch(struct solo_dev *solo_dev, u8 ch, int on)
{
	u8 ext_ch;

	if (ch < solo_dev->nr_chans) {
		solo_win_setup(solo_dev, ch, on ? 0 : solo_dev->video_hsize,
			       on ? 0 : solo_vlines(solo_dev),
			       solo_dev->video_hsize, solo_vlines(solo_dev),
			       on ? 1 : 0);
		return 0;
	}

	if (ch >= solo_dev->nr_chans + solo_dev->nr_ext)
		return -EINVAL;

	ext_ch = ch - solo_dev->nr_chans;

	/* 4up's first */
	if (ext_ch < 4)
		return solo_v4l2_ch_ext_4up(solo_dev, ext_ch, on);

	/* Remaining case is 16up for 16-port */
	return solo_v4l2_ch_ext_16up(solo_dev, on);
}