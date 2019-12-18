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
struct phylink {int /*<<< orphan*/  phylink_disable_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_LINK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phylink_run_resolve (struct phylink*) ; 

__attribute__((used)) static void phylink_sfp_link_up(void *upstream)
{
	struct phylink *pl = upstream;

	ASSERT_RTNL();

	clear_bit(PHYLINK_DISABLE_LINK, &pl->phylink_disable_state);
	phylink_run_resolve(pl);
}