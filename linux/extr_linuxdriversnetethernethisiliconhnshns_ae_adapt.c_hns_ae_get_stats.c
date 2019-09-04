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
typedef  int /*<<< orphan*/  u64 ;
struct hns_ppe_cb {int dummy; } ;
struct hns_mac_cb {scalar_t__ mac_type; } ;
struct hnae_vf_cb {int /*<<< orphan*/  port_index; int /*<<< orphan*/  dsaf_dev; } ;
struct hnae_handle {int q_num; int /*<<< orphan*/ * qs; } ;

/* Variables and functions */
 scalar_t__ ETH_SS_STATS ; 
 scalar_t__ HNAE_PORT_SERVICE ; 
 struct hnae_vf_cb* hns_ae_get_vf_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_dsaf_get_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 struct hns_ppe_cb* hns_get_ppe_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_mac_get_sset_count (struct hns_mac_cb*,int) ; 
 int /*<<< orphan*/  hns_mac_get_stats (struct hns_mac_cb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_ppe_get_sset_count (int) ; 
 int /*<<< orphan*/  hns_ppe_get_stats (struct hns_ppe_cb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_rcb_get_ring_sset_count (int) ; 
 int /*<<< orphan*/  hns_rcb_get_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void hns_ae_get_stats(struct hnae_handle *handle, u64 *data)
{
	int idx;
	struct hns_mac_cb *mac_cb;
	struct hns_ppe_cb *ppe_cb;
	u64 *p = data;
	struct  hnae_vf_cb *vf_cb;

	if (!handle || !data) {
		pr_err("hns_ae_get_stats NULL handle or data pointer!\n");
		return;
	}

	vf_cb = hns_ae_get_vf_cb(handle);
	mac_cb = hns_get_mac_cb(handle);
	ppe_cb = hns_get_ppe_cb(handle);

	for (idx = 0; idx < handle->q_num; idx++) {
		hns_rcb_get_stats(handle->qs[idx], p);
		p += hns_rcb_get_ring_sset_count((int)ETH_SS_STATS);
	}

	hns_ppe_get_stats(ppe_cb, p);
	p += hns_ppe_get_sset_count((int)ETH_SS_STATS);

	hns_mac_get_stats(mac_cb, p);
	p += hns_mac_get_sset_count(mac_cb, (int)ETH_SS_STATS);

	if (mac_cb->mac_type == HNAE_PORT_SERVICE)
		hns_dsaf_get_stats(vf_cb->dsaf_dev, p, vf_cb->port_index);
}