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
struct solo_dev {int nr_chans; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOLO_VI_WIN_CTRL0 (int) ; 
 int /*<<< orphan*/  SOLO_VI_WIN_CTRL1 (int) ; 
 int /*<<< orphan*/  SOLO_VI_WIN_ON (int) ; 
 int /*<<< orphan*/  SOLO_VO_BORDER_FILL_MASK ; 
 int /*<<< orphan*/  SOLO_VO_BORDER_LINE_MASK ; 
 int /*<<< orphan*/  SOLO_VO_BORDER_X (int) ; 
 int /*<<< orphan*/  SOLO_VO_BORDER_Y (int) ; 
 int /*<<< orphan*/  SOLO_VO_DISP_CTRL ; 
 int /*<<< orphan*/  SOLO_VO_FREEZE_CTRL ; 
 int /*<<< orphan*/  SOLO_VO_RECTANGLE_CTRL (int) ; 
 int /*<<< orphan*/  SOLO_VO_RECTANGLE_START (int) ; 
 int /*<<< orphan*/  SOLO_VO_RECTANGLE_STOP (int) ; 
 int /*<<< orphan*/  SOLO_VO_ZOOM_CTRL ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void solo_disp_exit(struct solo_dev *solo_dev)
{
	int i;

	solo_reg_write(solo_dev, SOLO_VO_DISP_CTRL, 0);
	solo_reg_write(solo_dev, SOLO_VO_ZOOM_CTRL, 0);
	solo_reg_write(solo_dev, SOLO_VO_FREEZE_CTRL, 0);

	for (i = 0; i < solo_dev->nr_chans; i++) {
		solo_reg_write(solo_dev, SOLO_VI_WIN_CTRL0(i), 0);
		solo_reg_write(solo_dev, SOLO_VI_WIN_CTRL1(i), 0);
		solo_reg_write(solo_dev, SOLO_VI_WIN_ON(i), 0);
	}

	/* Set default border */
	for (i = 0; i < 5; i++)
		solo_reg_write(solo_dev, SOLO_VO_BORDER_X(i), 0);

	for (i = 0; i < 5; i++)
		solo_reg_write(solo_dev, SOLO_VO_BORDER_Y(i), 0);

	solo_reg_write(solo_dev, SOLO_VO_BORDER_LINE_MASK, 0);
	solo_reg_write(solo_dev, SOLO_VO_BORDER_FILL_MASK, 0);

	solo_reg_write(solo_dev, SOLO_VO_RECTANGLE_CTRL(0), 0);
	solo_reg_write(solo_dev, SOLO_VO_RECTANGLE_START(0), 0);
	solo_reg_write(solo_dev, SOLO_VO_RECTANGLE_STOP(0), 0);

	solo_reg_write(solo_dev, SOLO_VO_RECTANGLE_CTRL(1), 0);
	solo_reg_write(solo_dev, SOLO_VO_RECTANGLE_START(1), 0);
	solo_reg_write(solo_dev, SOLO_VO_RECTANGLE_STOP(1), 0);
}