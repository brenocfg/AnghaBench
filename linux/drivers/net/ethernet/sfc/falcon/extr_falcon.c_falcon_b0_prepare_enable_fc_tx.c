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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  falcon_drain_tx_fifo (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_reconfigure_xmac (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_start_nic_stats (struct ef4_nic*) ; 
 int /*<<< orphan*/  falcon_stop_nic_stats (struct ef4_nic*) ; 

__attribute__((used)) static void falcon_b0_prepare_enable_fc_tx(struct ef4_nic *efx)
{
	/* Recover by resetting the EM block */
	falcon_stop_nic_stats(efx);
	falcon_drain_tx_fifo(efx);
	falcon_reconfigure_xmac(efx);
	falcon_start_nic_stats(efx);
}