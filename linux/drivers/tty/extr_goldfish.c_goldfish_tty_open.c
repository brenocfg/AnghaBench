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
struct tty_struct {size_t index; } ;
struct goldfish_tty {int /*<<< orphan*/  port; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct goldfish_tty* goldfish_ttys ; 
 int tty_port_open (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int goldfish_tty_open(struct tty_struct *tty, struct file *filp)
{
	struct goldfish_tty *qtty = &goldfish_ttys[tty->index];
	return tty_port_open(&qtty->port, tty, filp);
}