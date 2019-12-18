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
struct efx_nic {TYPE_2__* mcdi; } ;
struct TYPE_3__ {scalar_t__ logging_buffer; } ;
struct TYPE_4__ {TYPE_1__ iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

void efx_mcdi_fini(struct efx_nic *efx)
{
	if (!efx->mcdi)
		return;

#ifdef CONFIG_SFC_MCDI_LOGGING
	free_page((unsigned long)efx->mcdi->iface.logging_buffer);
#endif

	kfree(efx->mcdi);
}