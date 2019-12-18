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
struct phylink_link_state {int pause; } ;
struct TYPE_2__ {int pause; int /*<<< orphan*/  advertising; } ;
struct phylink {TYPE_1__ link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int MLO_PAUSE_AN ; 
 int MLO_PAUSE_ASYM ; 
 int MLO_PAUSE_RX ; 
 int MLO_PAUSE_SYM ; 
 int MLO_PAUSE_TX ; 
 int MLO_PAUSE_TXRX_MASK ; 
 int /*<<< orphan*/  Pause ; 
 scalar_t__ phylink_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phylink_resolve_flow(struct phylink *pl,
				 struct phylink_link_state *state)
{
	int new_pause = 0;

	if (pl->link_config.pause & MLO_PAUSE_AN) {
		int pause = 0;

		if (phylink_test(pl->link_config.advertising, Pause))
			pause |= MLO_PAUSE_SYM;
		if (phylink_test(pl->link_config.advertising, Asym_Pause))
			pause |= MLO_PAUSE_ASYM;

		pause &= state->pause;

		if (pause & MLO_PAUSE_SYM)
			new_pause = MLO_PAUSE_TX | MLO_PAUSE_RX;
		else if (pause & MLO_PAUSE_ASYM)
			new_pause = state->pause & MLO_PAUSE_SYM ?
				 MLO_PAUSE_TX : MLO_PAUSE_RX;
	} else {
		new_pause = pl->link_config.pause & MLO_PAUSE_TXRX_MASK;
	}

	state->pause &= ~MLO_PAUSE_TXRX_MASK;
	state->pause |= new_pause;
}