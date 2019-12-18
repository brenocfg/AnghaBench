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
struct tty_struct {struct gb_tty* driver_data; } ;
struct gb_tty {int ctrlout; int ctrlin; } ;

/* Variables and functions */
 int GB_UART_CTRL_DCD ; 
 int GB_UART_CTRL_DSR ; 
 int GB_UART_CTRL_DTR ; 
 int GB_UART_CTRL_RI ; 
 int GB_UART_CTRL_RTS ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RI ; 
 int TIOCM_RTS ; 

__attribute__((used)) static int gb_tty_tiocmget(struct tty_struct *tty)
{
	struct gb_tty *gb_tty = tty->driver_data;

	return (gb_tty->ctrlout & GB_UART_CTRL_DTR ? TIOCM_DTR : 0) |
	       (gb_tty->ctrlout & GB_UART_CTRL_RTS ? TIOCM_RTS : 0) |
	       (gb_tty->ctrlin  & GB_UART_CTRL_DSR ? TIOCM_DSR : 0) |
	       (gb_tty->ctrlin  & GB_UART_CTRL_RI  ? TIOCM_RI  : 0) |
	       (gb_tty->ctrlin  & GB_UART_CTRL_DCD ? TIOCM_CD  : 0) |
	       TIOCM_CTS;
}