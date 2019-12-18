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
union ef4_multicast_hash {int /*<<< orphan*/ * oword; } ;
struct ef4_nic {int /*<<< orphan*/  mac_lock; union ef4_multicast_hash multicast_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  FR_AB_MAC_MC_HASH_REG0 ; 
 int /*<<< orphan*/  FR_AB_MAC_MC_HASH_REG1 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void falcon_push_multicast_hash(struct ef4_nic *efx)
{
	union ef4_multicast_hash *mc_hash = &efx->multicast_hash;

	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	ef4_writeo(efx, &mc_hash->oword[0], FR_AB_MAC_MC_HASH_REG0);
	ef4_writeo(efx, &mc_hash->oword[1], FR_AB_MAC_MC_HASH_REG1);
}