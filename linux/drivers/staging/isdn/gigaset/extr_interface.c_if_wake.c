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
struct cardstate {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_wake(unsigned long data)
{
	struct cardstate *cs = (struct cardstate *)data;

	tty_port_tty_wakeup(&cs->port);
}