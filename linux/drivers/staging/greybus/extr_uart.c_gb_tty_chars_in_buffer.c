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
struct gb_tty {scalar_t__ credits; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  write_fifo; } ;

/* Variables and functions */
 scalar_t__ GB_UART_FIRMWARE_CREDITS ; 
 int kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gb_tty_chars_in_buffer(struct tty_struct *tty)
{
	struct gb_tty *gb_tty = tty->driver_data;
	unsigned long flags;
	int chars;

	spin_lock_irqsave(&gb_tty->write_lock, flags);
	chars = kfifo_len(&gb_tty->write_fifo);
	if (gb_tty->credits < GB_UART_FIRMWARE_CREDITS)
		chars += GB_UART_FIRMWARE_CREDITS - gb_tty->credits;
	spin_unlock_irqrestore(&gb_tty->write_lock, flags);

	return chars;
}