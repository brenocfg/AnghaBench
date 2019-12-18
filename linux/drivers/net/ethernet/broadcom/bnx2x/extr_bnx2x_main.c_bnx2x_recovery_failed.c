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
struct bnx2x {int /*<<< orphan*/  recovery_state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_RECOVERY_FAILED ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  bnx2x_set_power_state (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_reset_in_progress (struct bnx2x*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static void bnx2x_recovery_failed(struct bnx2x *bp)
{
	netdev_err(bp->dev, "Recovery has failed. Power cycle is needed.\n");

	/* Disconnect this device */
	netif_device_detach(bp->dev);

	/*
	 * Block ifup for all function on this engine until "process kill"
	 * or power cycle.
	 */
	bnx2x_set_reset_in_progress(bp);

	/* Shut down the power */
	bnx2x_set_power_state(bp, PCI_D3hot);

	bp->recovery_state = BNX2X_RECOVERY_FAILED;

	smp_mb();
}