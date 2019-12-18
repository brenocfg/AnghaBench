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
struct tty_struct {TYPE_1__* link; scalar_t__ stopped; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int tty_buffer_space_avail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pty_write_room(struct tty_struct *tty)
{
	if (tty->stopped)
		return 0;
	return tty_buffer_space_avail(tty->link->port);
}