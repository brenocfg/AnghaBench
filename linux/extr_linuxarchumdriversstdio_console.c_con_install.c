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
struct tty_driver {int dummy; } ;

/* Variables and functions */
 int line_install (struct tty_driver*,struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vts ; 

__attribute__((used)) static int con_install(struct tty_driver *driver, struct tty_struct *tty)
{
	return line_install(driver, tty, &vts[tty->index]);
}