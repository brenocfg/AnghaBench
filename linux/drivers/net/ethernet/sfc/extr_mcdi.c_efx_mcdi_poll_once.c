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
struct efx_mcdi_iface {int /*<<< orphan*/  iface_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mcdi_poll_response ) (struct efx_nic*) ;} ;

/* Variables and functions */
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_read_response_header (struct efx_nic*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static bool efx_mcdi_poll_once(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	rmb();
	if (!efx->type->mcdi_poll_response(efx))
		return false;

	spin_lock_bh(&mcdi->iface_lock);
	efx_mcdi_read_response_header(efx);
	spin_unlock_bh(&mcdi->iface_lock);

	return true;
}