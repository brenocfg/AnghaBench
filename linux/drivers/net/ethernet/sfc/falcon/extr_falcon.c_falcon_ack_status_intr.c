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
struct falcon_nic_data {scalar_t__ xmac_poll_required; } ;
struct TYPE_2__ {int /*<<< orphan*/  up; } ;
struct ef4_nic {TYPE_1__ link_state; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 scalar_t__ EF4_REV_FALCON_B0 ; 
 int /*<<< orphan*/  FR_AB_XM_MGT_INT_MSK ; 
 scalar_t__ LOOPBACK_INTERNAL (struct ef4_nic*) ; 
 scalar_t__ ef4_nic_rev (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void falcon_ack_status_intr(struct ef4_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	ef4_oword_t reg;

	if ((ef4_nic_rev(efx) != EF4_REV_FALCON_B0) || LOOPBACK_INTERNAL(efx))
		return;

	/* We expect xgmii faults if the wireside link is down */
	if (!efx->link_state.up)
		return;

	/* We can only use this interrupt to signal the negative edge of
	 * xaui_align [we have to poll the positive edge]. */
	if (nic_data->xmac_poll_required)
		return;

	ef4_reado(efx, &reg, FR_AB_XM_MGT_INT_MSK);
}