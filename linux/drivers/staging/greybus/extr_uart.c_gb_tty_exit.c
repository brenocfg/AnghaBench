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

/* Variables and functions */
 int /*<<< orphan*/  gb_tty_driver ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_minors ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_tty_exit(void)
{
	tty_unregister_driver(gb_tty_driver);
	put_tty_driver(gb_tty_driver);
	idr_destroy(&tty_minors);
}