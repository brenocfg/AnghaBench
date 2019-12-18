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
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qt2025c_restart_firmware (struct ef4_nic*) ; 
 int qt2025c_wait_fw_status_good (struct ef4_nic*) ; 
 int qt2025c_wait_heartbeat (struct ef4_nic*) ; 

__attribute__((used)) static int qt2025c_wait_reset(struct ef4_nic *efx)
{
	int rc;

	rc = qt2025c_wait_heartbeat(efx);
	if (rc != 0)
		return rc;

	rc = qt2025c_wait_fw_status_good(efx);
	if (rc == -ETIMEDOUT) {
		/* Bug 17689: occasionally heartbeat starts but firmware status
		 * code never progresses beyond 0x00.  Try again, once, after
		 * restarting execution of the firmware image. */
		netif_dbg(efx, hw, efx->net_dev,
			  "bashing QT2025C microcontroller\n");
		qt2025c_restart_firmware(efx);
		rc = qt2025c_wait_heartbeat(efx);
		if (rc != 0)
			return rc;
		rc = qt2025c_wait_fw_status_good(efx);
	}

	return rc;
}