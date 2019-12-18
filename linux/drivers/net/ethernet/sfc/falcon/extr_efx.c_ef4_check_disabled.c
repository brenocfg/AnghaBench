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
struct ef4_nic {scalar_t__ state; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ STATE_DISABLED ; 
 scalar_t__ STATE_RECOVERY ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ef4_check_disabled(struct ef4_nic *efx)
{
	if (efx->state == STATE_DISABLED || efx->state == STATE_RECOVERY) {
		netif_err(efx, drv, efx->net_dev,
			  "device is disabled due to earlier errors\n");
		return -EIO;
	}
	return 0;
}