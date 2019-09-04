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
struct tty_driver {int dummy; } ;
struct console {int flags; } ;

/* Variables and functions */
 int CON_ENABLED ; 
 struct tty_driver* nfcon_tty_driver ; 

__attribute__((used)) static struct tty_driver *nfcon_device(struct console *con, int *index)
{
	*index = 0;
	return (con->flags & CON_ENABLED) ? nfcon_tty_driver : NULL;
}