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
struct ath10k {int /*<<< orphan*/  num_peers; int /*<<< orphan*/  peer_delete_done; TYPE_1__ wmi; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  WMI_SERVICE_SYNC_DELETE_CMDS ; 
 int ath10k_wait_for_peer_deleted (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int ath10k_wmi_peer_delete (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_peer_delete(struct ath10k *ar, u32 vdev_id, const u8 *addr)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_wmi_peer_delete(ar, vdev_id, addr);
	if (ret)
		return ret;

	ret = ath10k_wait_for_peer_deleted(ar, vdev_id, addr);
	if (ret)
		return ret;

	if (test_bit(WMI_SERVICE_SYNC_DELETE_CMDS, ar->wmi.svc_map)) {
		unsigned long time_left;

		time_left = wait_for_completion_timeout
			    (&ar->peer_delete_done, 5 * HZ);

		if (!time_left) {
			ath10k_warn(ar, "Timeout in receiving peer delete response\n");
			return -ETIMEDOUT;
		}
	}

	ar->num_peers--;

	return 0;
}