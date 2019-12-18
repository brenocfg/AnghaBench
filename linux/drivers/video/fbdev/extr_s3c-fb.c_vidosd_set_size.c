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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ osd_size_off; } ;
struct s3c_fb_win {TYPE_1__ variant; int /*<<< orphan*/  index; struct s3c_fb* parent; } ;
struct s3c_fb {int /*<<< orphan*/  variant; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ OSD_BASE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vidosd_set_size(struct s3c_fb_win *win, u32 size)
{
	struct s3c_fb *sfb = win->parent;

	/* OSD can be set up if osd_size_off != 0 for this window */
	if (win->variant.osd_size_off)
		writel(size, sfb->regs + OSD_BASE(win->index, sfb->variant)
				+ win->variant.osd_size_off);
}