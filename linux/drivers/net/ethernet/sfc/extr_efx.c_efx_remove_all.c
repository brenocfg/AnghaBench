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
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* vswitching_remove ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  efx_remove_channels (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_filters (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_nic (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_remove_port (struct efx_nic*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static void efx_remove_all(struct efx_nic *efx)
{
	efx_remove_channels(efx);
	efx_remove_filters(efx);
#ifdef CONFIG_SFC_SRIOV
	efx->type->vswitching_remove(efx);
#endif
	efx_remove_port(efx);
	efx_remove_nic(efx);
}