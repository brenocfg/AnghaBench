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
struct solo_dev {scalar_t__ nr_chans; } ;

/* Variables and functions */
 int SOLO_VI_WIN_CHANNEL (scalar_t__) ; 
 int /*<<< orphan*/  SOLO_VI_WIN_CTRL0 (scalar_t__) ; 
 int /*<<< orphan*/  SOLO_VI_WIN_CTRL1 (scalar_t__) ; 
 int SOLO_VI_WIN_EX (int) ; 
 int SOLO_VI_WIN_EY (int) ; 
 int SOLO_VI_WIN_SCALE (int) ; 
 int SOLO_VI_WIN_SX (int) ; 
 int SOLO_VI_WIN_SY (int) ; 
 int /*<<< orphan*/  solo_reg_write (struct solo_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void solo_win_setup(struct solo_dev *solo_dev, u8 ch,
			   int sx, int sy, int ex, int ey, int scale)
{
	if (ch >= solo_dev->nr_chans)
		return;

	/* Here, we just keep window/channel the same */
	solo_reg_write(solo_dev, SOLO_VI_WIN_CTRL0(ch),
		       SOLO_VI_WIN_CHANNEL(ch) |
		       SOLO_VI_WIN_SX(sx) |
		       SOLO_VI_WIN_EX(ex) |
		       SOLO_VI_WIN_SCALE(scale));

	solo_reg_write(solo_dev, SOLO_VI_WIN_CTRL1(ch),
		       SOLO_VI_WIN_SY(sy) |
		       SOLO_VI_WIN_EY(ey));
}