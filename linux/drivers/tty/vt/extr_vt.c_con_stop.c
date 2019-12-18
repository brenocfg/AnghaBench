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
struct tty_struct {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc_cons_allocated (int) ; 
 int /*<<< orphan*/  vt_kbd_con_stop (int) ; 

__attribute__((used)) static void con_stop(struct tty_struct *tty)
{
	int console_num;
	if (!tty)
		return;
	console_num = tty->index;
	if (!vc_cons_allocated(console_num))
		return;
	vt_kbd_con_stop(console_num);
}