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
struct wmi_sta_keepalive_arg {int enabled; int /*<<< orphan*/  interval; int /*<<< orphan*/  method; int /*<<< orphan*/  vdev_id; } ;
struct ath10k_vif {scalar_t__ vdev_type; int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  svc_map; } ;
struct ath10k {TYPE_1__ wmi; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_SERVICE_STA_KEEP_ALIVE ; 
 int /*<<< orphan*/  WMI_STA_KEEPALIVE_INTERVAL_DISABLE ; 
 int /*<<< orphan*/  WMI_STA_KEEPALIVE_METHOD_NULL_FRAME ; 
 scalar_t__ WMI_VDEV_TYPE_STA ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_sta_keepalive (struct ath10k*,struct wmi_sta_keepalive_arg*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_mac_vif_disable_keepalive(struct ath10k_vif *arvif)
{
	struct ath10k *ar = arvif->ar;
	struct wmi_sta_keepalive_arg arg = {};
	int ret;

	lockdep_assert_held(&arvif->ar->conf_mutex);

	if (arvif->vdev_type != WMI_VDEV_TYPE_STA)
		return 0;

	if (!test_bit(WMI_SERVICE_STA_KEEP_ALIVE, ar->wmi.svc_map))
		return 0;

	/* Some firmware revisions have a bug and ignore the `enabled` field.
	 * Instead use the interval to disable the keepalive.
	 */
	arg.vdev_id = arvif->vdev_id;
	arg.enabled = 1;
	arg.method = WMI_STA_KEEPALIVE_METHOD_NULL_FRAME;
	arg.interval = WMI_STA_KEEPALIVE_INTERVAL_DISABLE;

	ret = ath10k_wmi_sta_keepalive(ar, &arg);
	if (ret) {
		ath10k_warn(ar, "failed to submit keepalive on vdev %i: %d\n",
			    arvif->vdev_id, ret);
		return ret;
	}

	return 0;
}