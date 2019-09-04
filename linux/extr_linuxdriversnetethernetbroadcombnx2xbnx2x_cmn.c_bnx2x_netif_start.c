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
struct bnx2x {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNX2X_STATE_OPEN ; 
 scalar_t__ CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_int_enable (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_napi_enable (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_napi_enable_cnic (struct bnx2x*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 

void bnx2x_netif_start(struct bnx2x *bp)
{
	if (netif_running(bp->dev)) {
		bnx2x_napi_enable(bp);
		if (CNIC_LOADED(bp))
			bnx2x_napi_enable_cnic(bp);
		bnx2x_int_enable(bp);
		if (bp->state == BNX2X_STATE_OPEN)
			netif_tx_wake_all_queues(bp->dev);
	}
}