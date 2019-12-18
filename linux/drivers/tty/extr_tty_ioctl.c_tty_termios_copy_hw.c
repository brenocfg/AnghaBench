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
struct ktermios {int c_cflag; int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; } ;

/* Variables and functions */
 int CLOCAL ; 
 int CREAD ; 
 int HUPCL ; 

void tty_termios_copy_hw(struct ktermios *new, struct ktermios *old)
{
	/* The bits a dumb device handles in software. Smart devices need
	   to always provide a set_termios method */
	new->c_cflag &= HUPCL | CREAD | CLOCAL;
	new->c_cflag |= old->c_cflag & ~(HUPCL | CREAD | CLOCAL);
	new->c_ispeed = old->c_ispeed;
	new->c_ospeed = old->c_ospeed;
}