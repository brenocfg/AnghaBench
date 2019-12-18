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
struct sg_table {int dummy; } ;
struct msc_window {int dummy; } ;
struct msc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIN_LOCKED ; 
 int /*<<< orphan*/  WIN_READY ; 
 struct msc* dev_get_drvdata (struct device*) ; 
 struct msc_window* msc_find_window (struct msc*,struct sg_table*,int) ; 
 int /*<<< orphan*/  msc_win_set_lockout (struct msc_window*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_th_msc_window_unlock(struct device *dev, struct sg_table *sgt)
{
	struct msc *msc = dev_get_drvdata(dev);
	struct msc_window *win;

	if (!sgt)
		return;

	win = msc_find_window(msc, sgt, false);
	if (!win)
		return;

	msc_win_set_lockout(win, WIN_LOCKED, WIN_READY);
}