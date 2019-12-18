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
struct wmi_pno_scan_req {int /*<<< orphan*/  enable; } ;
struct ath10k_vif {int vdev_type; int /*<<< orphan*/  vdev_id; struct ath10k* ar; } ;
struct ath10k {int nlo_enabled; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  WMI_VDEV_TYPE_STA 128 
 int ath10k_wmi_wow_config_pno (struct ath10k*,int /*<<< orphan*/ ,struct wmi_pno_scan_req*) ; 
 int /*<<< orphan*/  kfree (struct wmi_pno_scan_req*) ; 
 struct wmi_pno_scan_req* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_vif_wow_clean_nlo(struct ath10k_vif *arvif)
{
	int ret = 0;
	struct ath10k *ar = arvif->ar;

	switch (arvif->vdev_type) {
	case WMI_VDEV_TYPE_STA:
		if (ar->nlo_enabled) {
			struct wmi_pno_scan_req *pno;

			pno = kzalloc(sizeof(*pno), GFP_KERNEL);
			if (!pno)
				return -ENOMEM;

			pno->enable = 0;
			ar->nlo_enabled = false;
			ret = ath10k_wmi_wow_config_pno(ar, arvif->vdev_id, pno);
			kfree(pno);
		}
		break;
	default:
		break;
	}
	return ret;
}