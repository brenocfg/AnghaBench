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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int efx_mcdi_exit_assertion (struct efx_nic*) ; 
 int efx_mcdi_read_assertion (struct efx_nic*) ; 

int efx_mcdi_handle_assertion(struct efx_nic *efx)
{
	int rc;

	rc = efx_mcdi_read_assertion(efx);
	if (rc <= 0)
		return rc;

	return efx_mcdi_exit_assertion(efx);
}