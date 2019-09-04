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
struct hns_mac_cb {int dummy; } ;
struct hnae_handle {int /*<<< orphan*/  q_num; int /*<<< orphan*/  qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCB_INT_FLAG_RX ; 
 int /*<<< orphan*/  RCB_INT_FLAG_TX ; 
 int /*<<< orphan*/  hns_ae_ring_enable_all (struct hnae_handle*,int /*<<< orphan*/ ) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_mac_stop (struct hns_mac_cb*) ; 
 int /*<<< orphan*/  hns_mac_vm_config_bc_en (struct hns_mac_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_rcb_wait_fbd_clean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void hns_ae_stop(struct hnae_handle *handle)
{
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	/* just clean tx fbd, neednot rx fbd*/
	hns_rcb_wait_fbd_clean(handle->qs, handle->q_num, RCB_INT_FLAG_TX);

	msleep(20);

	hns_mac_stop(mac_cb);

	usleep_range(10000, 20000);

	hns_ae_ring_enable_all(handle, 0);

	/* clean rx fbd. */
	hns_rcb_wait_fbd_clean(handle->qs, handle->q_num, RCB_INT_FLAG_RX);

	(void)hns_mac_vm_config_bc_en(mac_cb, 0, false);
}