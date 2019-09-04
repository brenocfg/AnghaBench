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
struct hns_mac_cb {TYPE_1__* dsaf_dev; } ;
struct hnae_handle {int q_num; int /*<<< orphan*/ * qs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int RCB_INT_FLAG_RX ; 
 int RCB_INT_FLAG_TX ; 
 int /*<<< orphan*/  hns_ae_ring_enable_all (struct hnae_handle*,int) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_mac_start (struct hns_mac_cb*) ; 
 int hns_mac_vm_config_bc_en (struct hns_mac_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_rcb_int_clr_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_rcbv2_int_clr_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hns_ae_start(struct hnae_handle *handle)
{
	int ret;
	int k;
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	ret = hns_mac_vm_config_bc_en(mac_cb, 0, true);
	if (ret)
		return ret;

	for (k = 0; k < handle->q_num; k++) {
		if (AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver))
			hns_rcb_int_clr_hw(handle->qs[k],
					   RCB_INT_FLAG_TX | RCB_INT_FLAG_RX);
		else
			hns_rcbv2_int_clr_hw(handle->qs[k],
					     RCB_INT_FLAG_TX | RCB_INT_FLAG_RX);
	}
	hns_ae_ring_enable_all(handle, 1);
	msleep(100);

	hns_mac_start(mac_cb);

	return 0;
}