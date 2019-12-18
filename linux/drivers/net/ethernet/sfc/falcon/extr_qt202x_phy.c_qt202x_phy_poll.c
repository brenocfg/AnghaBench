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
struct TYPE_2__ {int up; int speed; int fd; int /*<<< orphan*/  fc; } ;
struct ef4_nic {scalar_t__ phy_type; TYPE_1__ link_state; int /*<<< orphan*/  wanted_fc; } ;

/* Variables and functions */
 scalar_t__ PHY_TYPE_QT2025C ; 
 int /*<<< orphan*/  qt2025c_bug17190_workaround (struct ef4_nic*) ; 
 int qt202x_link_ok (struct ef4_nic*) ; 

__attribute__((used)) static bool qt202x_phy_poll(struct ef4_nic *efx)
{
	bool was_up = efx->link_state.up;

	efx->link_state.up = qt202x_link_ok(efx);
	efx->link_state.speed = 10000;
	efx->link_state.fd = true;
	efx->link_state.fc = efx->wanted_fc;

	if (efx->phy_type == PHY_TYPE_QT2025C)
		qt2025c_bug17190_workaround(efx);

	return efx->link_state.up != was_up;
}