#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phylink_link_state {int link; scalar_t__ an_complete; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  an_enabled; int /*<<< orphan*/  interface; int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; } ;
struct TYPE_4__ {int /*<<< orphan*/  an_enabled; int /*<<< orphan*/  interface; int /*<<< orphan*/  advertising; } ;
struct phylink {int /*<<< orphan*/  config; TYPE_1__* ops; TYPE_2__ link_config; } ;
struct TYPE_3__ {int (* mac_link_state ) (int /*<<< orphan*/ ,struct phylink_link_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  MLO_PAUSE_NONE ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_zero (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct phylink_link_state*) ; 

__attribute__((used)) static int phylink_get_mac_state(struct phylink *pl, struct phylink_link_state *state)
{

	linkmode_copy(state->advertising, pl->link_config.advertising);
	linkmode_zero(state->lp_advertising);
	state->interface = pl->link_config.interface;
	state->an_enabled = pl->link_config.an_enabled;
	state->speed = SPEED_UNKNOWN;
	state->duplex = DUPLEX_UNKNOWN;
	state->pause = MLO_PAUSE_NONE;
	state->an_complete = 0;
	state->link = 1;

	return pl->ops->mac_link_state(pl->config, state);
}