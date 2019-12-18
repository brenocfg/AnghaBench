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
struct ef4_link_state {int speed; int fd; int /*<<< orphan*/  up; int /*<<< orphan*/  fc; } ;
struct ef4_nic {struct ef4_link_state link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_link_state_equal (struct ef4_link_state*,struct ef4_link_state*) ; 
 int /*<<< orphan*/  ef4_mdio_get_pause (struct ef4_nic*) ; 
 int /*<<< orphan*/  sfx7101_check_bad_lp (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfx7101_link_ok (struct ef4_nic*) ; 

__attribute__((used)) static bool tenxpress_phy_poll(struct ef4_nic *efx)
{
	struct ef4_link_state old_state = efx->link_state;

	efx->link_state.up = sfx7101_link_ok(efx);
	efx->link_state.speed = 10000;
	efx->link_state.fd = true;
	efx->link_state.fc = ef4_mdio_get_pause(efx);

	sfx7101_check_bad_lp(efx, efx->link_state.up);

	return !ef4_link_state_equal(&efx->link_state, &old_state);
}