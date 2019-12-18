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
struct efx_nic {int wanted_fc; int /*<<< orphan*/ * link_advertising; } ;

/* Variables and functions */
 unsigned long const ADVERTISED_Asym_Pause ; 
 int /*<<< orphan*/  ADVERTISED_Autoneg ; 
 unsigned long const ADVERTISED_Pause ; 
 int EFX_FC_RX ; 
 int EFX_FC_TX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned long const*,int) ; 

void efx_link_set_advertising(struct efx_nic *efx,
			      const unsigned long *advertising)
{
	memcpy(efx->link_advertising, advertising,
	       sizeof(__ETHTOOL_DECLARE_LINK_MODE_MASK()));

	efx->link_advertising[0] |= ADVERTISED_Autoneg;
	if (advertising[0] & ADVERTISED_Pause)
		efx->wanted_fc |= (EFX_FC_TX | EFX_FC_RX);
	else
		efx->wanted_fc &= ~(EFX_FC_TX | EFX_FC_RX);
	if (advertising[0] & ADVERTISED_Asym_Pause)
		efx->wanted_fc ^= EFX_FC_TX;
}