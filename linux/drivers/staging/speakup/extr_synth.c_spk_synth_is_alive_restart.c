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
struct spk_synth {int alive; int /*<<< orphan*/  long_name; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ spk_wait_for_xmitr (struct spk_synth*) ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

int spk_synth_is_alive_restart(struct spk_synth *synth)
{
	if (synth->alive)
		return 1;
	if (spk_wait_for_xmitr(synth) > 0) {
		/* restart */
		synth->alive = 1;
		synth_printf("%s", synth->init);
		return 2; /* reenabled */
	}
	pr_warn("%s: can't restart synth\n", synth->long_name);
	return 0;
}