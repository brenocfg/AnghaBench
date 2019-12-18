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
struct efx_ptp_data {int reset_required; int /*<<< orphan*/  work; int /*<<< orphan*/  workwq; int /*<<< orphan*/  evt_frag_idx; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct efx_ptp_data* ptp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ptp_event_failure(struct efx_nic *efx, int expected_frag_len)
{
	struct efx_ptp_data *ptp = efx->ptp_data;

	netif_err(efx, hw, efx->net_dev,
		"PTP unexpected event length: got %d expected %d\n",
		ptp->evt_frag_idx, expected_frag_len);
	ptp->reset_required = true;
	queue_work(ptp->workwq, &ptp->work);
}