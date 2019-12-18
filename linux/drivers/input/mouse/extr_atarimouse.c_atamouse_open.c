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
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atamouse_interrupt ; 
 int /*<<< orphan*/  atari_input_mouse_interrupt_hook ; 
 scalar_t__ atari_mouse_buttons ; 
 int /*<<< orphan*/  ikbd_mouse_rel_pos () ; 
 int /*<<< orphan*/  ikbd_mouse_thresh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ikbd_mouse_y0_top () ; 
 int /*<<< orphan*/ * mouse_threshold ; 

__attribute__((used)) static int atamouse_open(struct input_dev *dev)
{
#ifdef FIXED_ATARI_JOYSTICK
	atari_mouse_buttons = 0;
#endif
	ikbd_mouse_y0_top();
	ikbd_mouse_thresh(mouse_threshold[0], mouse_threshold[1]);
	ikbd_mouse_rel_pos();
	atari_input_mouse_interrupt_hook = atamouse_interrupt;

	return 0;
}