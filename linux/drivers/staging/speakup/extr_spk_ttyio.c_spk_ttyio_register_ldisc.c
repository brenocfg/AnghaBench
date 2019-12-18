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
 int /*<<< orphan*/  N_SPEAKUP ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  spk_ttyio_ldisc_ops ; 
 scalar_t__ tty_register_ldisc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void spk_ttyio_register_ldisc(void)
{
	if (tty_register_ldisc(N_SPEAKUP, &spk_ttyio_ldisc_ops))
		pr_warn("speakup: Error registering line discipline. Most synths won't work.\n");
}