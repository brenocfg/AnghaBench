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
struct solo_dev {int nr_chans; int video_hsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_DEF_MOT_THRESH ; 
 int SOLO_MOTION_EXT_ADDR (struct solo_dev*) ; 
 int SOLO_MOT_FLAG_AREA ; 
 int SOLO_MOT_FLAG_SIZE ; 
 int SOLO_MOT_THRESH_SIZE ; 
 int /*<<< orphan*/  SOLO_VI_MOTION_BAR ; 
 int /*<<< orphan*/  SOLO_VI_MOTION_BORDER ; 
 int SOLO_VI_MOTION_EN (int /*<<< orphan*/ ) ; 
 int SOLO_VI_MOTION_FRAME_COUNT (int) ; 
 int SOLO_VI_MOTION_SAMPLE_COUNT (int) ; 
 int SOLO_VI_MOTION_SAMPLE_LENGTH (int) ; 
 int /*<<< orphan*/  SOLO_VI_MOT_ADR ; 
 int /*<<< orphan*/  SOLO_VI_MOT_CTRL ; 
 int /*<<< orphan*/  solo_dma_vin_region (struct solo_dev*,int,int,int) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  solo_set_motion_threshold (struct solo_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void solo_motion_config(struct solo_dev *solo_dev)
{
	int i;

	for (i = 0; i < solo_dev->nr_chans; i++) {
		/* Clear motion flag area */
		solo_dma_vin_region(solo_dev, i * SOLO_MOT_FLAG_SIZE, 0x0000,
				    SOLO_MOT_FLAG_SIZE);

		/* Clear working cache table */
		solo_dma_vin_region(solo_dev, SOLO_MOT_FLAG_AREA +
				    (i * SOLO_MOT_THRESH_SIZE * 2) +
				    SOLO_MOT_THRESH_SIZE, 0x0000,
				    SOLO_MOT_THRESH_SIZE);

		/* Set default threshold table */
		solo_set_motion_threshold(solo_dev, i, SOLO_DEF_MOT_THRESH);
	}

	/* Default motion settings */
	solo_reg_write(solo_dev, SOLO_VI_MOT_ADR, SOLO_VI_MOTION_EN(0) |
		       (SOLO_MOTION_EXT_ADDR(solo_dev) >> 16));
	solo_reg_write(solo_dev, SOLO_VI_MOT_CTRL,
		       SOLO_VI_MOTION_FRAME_COUNT(3) |
		       SOLO_VI_MOTION_SAMPLE_LENGTH(solo_dev->video_hsize / 16)
		       /* | SOLO_VI_MOTION_INTR_START_STOP */
		       | SOLO_VI_MOTION_SAMPLE_COUNT(10));

	solo_reg_write(solo_dev, SOLO_VI_MOTION_BORDER, 0);
	solo_reg_write(solo_dev, SOLO_VI_MOTION_BAR, 0);
}