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
struct uart_sunzilog_port {int /*<<< orphan*/  serio; scalar_t__ serio_open; } ;

/* Variables and functions */
 scalar_t__ ZS_IS_KEYB (struct uart_sunzilog_port*) ; 
 scalar_t__ ZS_IS_MOUSE (struct uart_sunzilog_port*) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ *,unsigned char,int /*<<< orphan*/ ) ; 
 int suncore_mouse_baud_detection (unsigned char,int) ; 
 int /*<<< orphan*/  sunzilog_change_mouse_baud (struct uart_sunzilog_port*) ; 

__attribute__((used)) static void sunzilog_kbdms_receive_chars(struct uart_sunzilog_port *up,
					 unsigned char ch, int is_break)
{
	if (ZS_IS_KEYB(up)) {
		/* Stop-A is handled by drivers/char/keyboard.c now. */
#ifdef CONFIG_SERIO
		if (up->serio_open)
			serio_interrupt(&up->serio, ch, 0);
#endif
	} else if (ZS_IS_MOUSE(up)) {
		int ret = suncore_mouse_baud_detection(ch, is_break);

		switch (ret) {
		case 2:
			sunzilog_change_mouse_baud(up);
			/* fallthru */
		case 1:
			break;

		case 0:
#ifdef CONFIG_SERIO
			if (up->serio_open)
				serio_interrupt(&up->serio, ch, 0);
#endif
			break;
		}
	}
}