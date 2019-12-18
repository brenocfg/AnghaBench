#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ (* update_lna ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct dib7000p_state {int /*<<< orphan*/  demod; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dib7000p_restart_agc (struct dib7000p_state*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib7000p_update_lna(struct dib7000p_state *state)
{
	u16 dyn_gain;

	if (state->cfg.update_lna) {
		dyn_gain = dib7000p_read_word(state, 394);
		if (state->cfg.update_lna(&state->demod, dyn_gain)) {
			dib7000p_restart_agc(state);
			return 1;
		}
	}

	return 0;
}