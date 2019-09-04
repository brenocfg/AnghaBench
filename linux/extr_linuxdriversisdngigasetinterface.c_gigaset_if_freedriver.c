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
struct gigaset_driver {int /*<<< orphan*/  tty; scalar_t__ have_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ ) ; 

void gigaset_if_freedriver(struct gigaset_driver *drv)
{
	if (!drv->have_tty)
		return;

	drv->have_tty = 0;
	tty_unregister_driver(drv->tty);
	put_tty_driver(drv->tty);
}