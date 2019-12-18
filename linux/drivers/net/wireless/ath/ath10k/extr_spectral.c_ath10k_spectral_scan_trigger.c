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
struct ath10k_vif {int vdev_id; } ;
struct TYPE_2__ {scalar_t__ mode; } ;
struct ath10k {TYPE_1__ spectral; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SPECTRAL_DISABLED ; 
 int /*<<< orphan*/  WMI_SPECTRAL_ENABLE_CMD_ENABLE ; 
 int /*<<< orphan*/  WMI_SPECTRAL_TRIGGER_CMD_CLEAR ; 
 int /*<<< orphan*/  WMI_SPECTRAL_TRIGGER_CMD_TRIGGER ; 
 struct ath10k_vif* ath10k_get_spectral_vdev (struct ath10k*) ; 
 int ath10k_wmi_vdev_spectral_enable (struct ath10k*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_spectral_scan_trigger(struct ath10k *ar)
{
	struct ath10k_vif *arvif;
	int res;
	int vdev_id;

	lockdep_assert_held(&ar->conf_mutex);

	arvif = ath10k_get_spectral_vdev(ar);
	if (!arvif)
		return -ENODEV;
	vdev_id = arvif->vdev_id;

	if (ar->spectral.mode == SPECTRAL_DISABLED)
		return 0;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_CLEAR,
					      WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	if (res < 0)
		return res;

	res = ath10k_wmi_vdev_spectral_enable(ar, vdev_id,
					      WMI_SPECTRAL_TRIGGER_CMD_TRIGGER,
					      WMI_SPECTRAL_ENABLE_CMD_ENABLE);
	if (res < 0)
		return res;

	return 0;
}