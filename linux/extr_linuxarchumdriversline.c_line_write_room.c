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
struct tty_struct {struct line* driver_data; } ;
struct line {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int write_room (struct line*) ; 

int line_write_room(struct tty_struct *tty)
{
	struct line *line = tty->driver_data;
	unsigned long flags;
	int room;

	spin_lock_irqsave(&line->lock, flags);
	room = write_room(line);
	spin_unlock_irqrestore(&line->lock, flags);

	return room;
}