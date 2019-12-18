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
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct efx_nic {TYPE_1__* ptp_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int EFAULT ; 
 int EOPNOTSUPP ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int efx_ptp_get_ts_config(struct efx_nic *efx, struct ifreq *ifr)
{
	if (!efx->ptp_data)
		return -EOPNOTSUPP;

	return copy_to_user(ifr->ifr_data, &efx->ptp_data->config,
			    sizeof(efx->ptp_data->config)) ? -EFAULT : 0;
}