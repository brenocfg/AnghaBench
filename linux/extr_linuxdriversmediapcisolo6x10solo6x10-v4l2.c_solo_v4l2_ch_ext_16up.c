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
struct solo_dev {int video_hsize; } ;

/* Variables and functions */
 int solo_vlines (struct solo_dev*) ; 
 int /*<<< orphan*/  solo_win_setup (struct solo_dev*,int,int,int,int,int,int) ; 

__attribute__((used)) static int solo_v4l2_ch_ext_16up(struct solo_dev *solo_dev, int on)
{
	int sy, ysize, hsize, i;

	if (!on) {
		for (i = 0; i < 16; i++)
			solo_win_setup(solo_dev, i, solo_dev->video_hsize,
				       solo_vlines(solo_dev),
				       solo_dev->video_hsize,
				       solo_vlines(solo_dev), 0);
		return 0;
	}

	ysize = solo_vlines(solo_dev) / 4;
	hsize = solo_dev->video_hsize / 4;

	for (sy = 0, i = 0; i < 4; i++, sy += ysize) {
		solo_win_setup(solo_dev, i * 4, 0, sy, hsize,
			       sy + ysize, 5);
		solo_win_setup(solo_dev, (i * 4) + 1, hsize, sy,
			       hsize * 2, sy + ysize, 5);
		solo_win_setup(solo_dev, (i * 4) + 2, hsize * 2, sy,
			       hsize * 3, sy + ysize, 5);
		solo_win_setup(solo_dev, (i * 4) + 3, hsize * 3, sy,
			       solo_dev->video_hsize, sy + ysize, 5);
	}

	return 0;
}