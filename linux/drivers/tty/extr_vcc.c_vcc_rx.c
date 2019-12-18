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
struct tty_struct {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ ) ; 
 int tty_insert_flip_string (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vcc_rx(struct tty_struct *tty, char *buf, int size)
{
	int len = 0;

	if (WARN_ON(!tty || !tty->port))
		return len;

	len = tty_insert_flip_string(tty->port, buf, size);
	if (len)
		tty_flip_buffer_push(tty->port);

	return len;
}