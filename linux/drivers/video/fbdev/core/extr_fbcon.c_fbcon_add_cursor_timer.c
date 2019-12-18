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
struct fbcon_ops {int flags; scalar_t__ cur_blink_jiffies; int /*<<< orphan*/  cursor_timer; } ;
struct TYPE_2__ {scalar_t__ func; } ;
struct fb_info {TYPE_1__ queue; struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */
 int FBCON_FLAGS_CURSOR_TIMER ; 
 int /*<<< orphan*/  INIT_WORK (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cursor_timer_handler ; 
 scalar_t__ fb_flashcursor ; 
 int /*<<< orphan*/  fbcon_cursor_noblink ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fbcon_add_cursor_timer(struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;

	if ((!info->queue.func || info->queue.func == fb_flashcursor) &&
	    !(ops->flags & FBCON_FLAGS_CURSOR_TIMER) &&
	    !fbcon_cursor_noblink) {
		if (!info->queue.func)
			INIT_WORK(&info->queue, fb_flashcursor);

		timer_setup(&ops->cursor_timer, cursor_timer_handler, 0);
		mod_timer(&ops->cursor_timer, jiffies + ops->cur_blink_jiffies);
		ops->flags |= FBCON_FLAGS_CURSOR_TIMER;
	}
}