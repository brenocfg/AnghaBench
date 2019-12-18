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

/* Variables and functions */
 int TTY_MAX_COUNT ; 
 struct tty_driver** gdm_driver ; 
 int /*<<< orphan*/  put_tty_driver (struct tty_driver*) ; 
 int /*<<< orphan*/  tty_unregister_driver (struct tty_driver*) ; 

void unregister_lte_tty_driver(void)
{
	struct tty_driver *tty_driver;
	int i;

	for (i = 0; i < TTY_MAX_COUNT; i++) {
		tty_driver = gdm_driver[i];
		if (tty_driver) {
			tty_unregister_driver(tty_driver);
			put_tty_driver(tty_driver);
		}
	}
}