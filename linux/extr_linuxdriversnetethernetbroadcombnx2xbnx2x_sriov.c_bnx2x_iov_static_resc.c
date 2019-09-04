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
struct vf_pf_resc_request {int /*<<< orphan*/  num_sbs; scalar_t__ num_mc_filters; int /*<<< orphan*/  num_vlan_filters; int /*<<< orphan*/  num_mac_filters; scalar_t__ num_txqs; scalar_t__ num_rxqs; } ;
struct bnx2x_virtf {int /*<<< orphan*/  sb_count; struct vf_pf_resc_request alloc_resc; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VF_MAC_CREDIT_CNT ; 
 int /*<<< orphan*/  VF_VLAN_CREDIT_CNT ; 

__attribute__((used)) static void
bnx2x_iov_static_resc(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	struct vf_pf_resc_request *resc = &vf->alloc_resc;

	/* will be set only during VF-ACQUIRE */
	resc->num_rxqs = 0;
	resc->num_txqs = 0;

	resc->num_mac_filters = VF_MAC_CREDIT_CNT;
	resc->num_vlan_filters = VF_VLAN_CREDIT_CNT;

	/* no real limitation */
	resc->num_mc_filters = 0;

	/* num_sbs already set */
	resc->num_sbs = vf->sb_count;
}