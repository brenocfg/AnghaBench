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
struct TYPE_2__ {scalar_t__ (* update_lna ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct dib8000_state {int /*<<< orphan*/ * fe; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_restart_agc (struct dib8000_state*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib8000_update_lna(struct dib8000_state *state)
{
	u16 dyn_gain;

	if (state->cfg.update_lna) {
		// read dyn_gain here (because it is demod-dependent and not tuner)
		dyn_gain = dib8000_read_word(state, 390);

		if (state->cfg.update_lna(state->fe[0], dyn_gain)) {
			dib8000_restart_agc(state);
			return 1;
		}
	}
	return 0;
}