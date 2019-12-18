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
struct phylink_link_state {scalar_t__ an_enabled; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_merge_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phylink_get_ksettings(const struct phylink_link_state *state,
				  struct ethtool_link_ksettings *kset)
{
	phylink_merge_link_mode(kset->link_modes.advertising, state->advertising);
	linkmode_copy(kset->link_modes.lp_advertising, state->lp_advertising);
	kset->base.speed = state->speed;
	kset->base.duplex = state->duplex;
	kset->base.autoneg = state->an_enabled ? AUTONEG_ENABLE :
				AUTONEG_DISABLE;
}