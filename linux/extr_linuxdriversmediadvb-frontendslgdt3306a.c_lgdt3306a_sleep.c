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
struct lgdt3306a_state {int current_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*) ; 
 scalar_t__ lg_chkerr (int) ; 
 int lgdt3306a_mpeg_tristate (struct lgdt3306a_state*,int) ; 
 int lgdt3306a_power (struct lgdt3306a_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lgdt3306a_sleep(struct lgdt3306a_state *state)
{
	int ret;

	dbg_info("\n");
	state->current_frequency = -1; /* force re-tune, when we wake */

	ret = lgdt3306a_mpeg_tristate(state, 1); /* disable data bus */
	if (lg_chkerr(ret))
		goto fail;

	ret = lgdt3306a_power(state, 0); /* power down */
	lg_chkerr(ret);

fail:
	return 0;
}