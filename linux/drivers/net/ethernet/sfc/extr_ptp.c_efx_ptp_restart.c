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
struct efx_nic {TYPE_1__* ptp_data; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int efx_ptp_start (struct efx_nic*) ; 

__attribute__((used)) static int efx_ptp_restart(struct efx_nic *efx)
{
	if (efx->ptp_data && efx->ptp_data->enabled)
		return efx_ptp_start(efx);
	return 0;
}