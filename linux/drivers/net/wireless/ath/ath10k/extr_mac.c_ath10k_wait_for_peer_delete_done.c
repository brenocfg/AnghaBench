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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {int /*<<< orphan*/  peer_delete_done; TYPE_1__ wmi; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  WMI_SERVICE_SYNC_DELETE_CMDS ; 
 int ath10k_wait_for_peer_deleted (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ath10k_wait_for_peer_delete_done(struct ath10k *ar, u32 vdev_id,
					     const u8 *addr)
{
	unsigned long time_left;
	int ret;

	if (test_bit(WMI_SERVICE_SYNC_DELETE_CMDS, ar->wmi.svc_map)) {
		ret = ath10k_wait_for_peer_deleted(ar, vdev_id, addr);
		if (ret) {
			ath10k_warn(ar, "failed wait for peer deleted");
			return;
		}

		time_left = wait_for_completion_timeout(&ar->peer_delete_done,
							5 * HZ);
		if (!time_left)
			ath10k_warn(ar, "Timeout in receiving peer delete response\n");
	}
}