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
struct bnx2 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2_cnic_stop (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_disable_int_sync (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_napi_disable (struct bnx2*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_netif_stop(struct bnx2 *bp, bool stop_cnic)
{
	if (stop_cnic)
		bnx2_cnic_stop(bp);
	if (netif_running(bp->dev)) {
		bnx2_napi_disable(bp);
		netif_tx_disable(bp->dev);
	}
	bnx2_disable_int_sync(bp);
	netif_carrier_off(bp->dev);	/* prevent tx timeout */
}