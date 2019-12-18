#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hns_ppe_cb {int dummy; } ;
struct hnae_vf_cb {int /*<<< orphan*/  port_index; TYPE_3__* dsaf_dev; TYPE_1__* mac_cb; } ;
struct hnae_handle {int q_num; int /*<<< orphan*/ * qs; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rcb_common; } ;
struct TYPE_4__ {scalar_t__ mac_type; } ;

/* Variables and functions */
 scalar_t__ HNAE_PORT_SERVICE ; 
 struct hnae_vf_cb* hns_ae_get_vf_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_dsaf_get_regs (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hns_ppe_cb* hns_get_ppe_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_mac_get_regs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_mac_get_regs_count (TYPE_1__*) ; 
 int /*<<< orphan*/  hns_ppe_get_regs (struct hns_ppe_cb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_ppe_get_regs_count () ; 
 int /*<<< orphan*/  hns_rcb_get_common_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_rcb_get_common_regs_count () ; 
 int /*<<< orphan*/  hns_rcb_get_ring_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hns_rcb_get_ring_regs_count () ; 

__attribute__((used)) static void hns_ae_get_regs(struct hnae_handle *handle, void *data)
{
	u32 *p = data;
	int i;
	struct hnae_vf_cb *vf_cb = hns_ae_get_vf_cb(handle);
	struct hns_ppe_cb *ppe_cb = hns_get_ppe_cb(handle);

	hns_ppe_get_regs(ppe_cb, p);
	p += hns_ppe_get_regs_count();

	hns_rcb_get_common_regs(vf_cb->dsaf_dev->rcb_common[0], p);
	p += hns_rcb_get_common_regs_count();

	for (i = 0; i < handle->q_num; i++) {
		hns_rcb_get_ring_regs(handle->qs[i], p);
		p += hns_rcb_get_ring_regs_count();
	}

	hns_mac_get_regs(vf_cb->mac_cb, p);
	p += hns_mac_get_regs_count(vf_cb->mac_cb);

	if (vf_cb->mac_cb->mac_type == HNAE_PORT_SERVICE)
		hns_dsaf_get_regs(vf_cb->dsaf_dev, vf_cb->port_index, p);
}