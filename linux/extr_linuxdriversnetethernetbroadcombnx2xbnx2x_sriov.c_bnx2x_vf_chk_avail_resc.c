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
typedef  scalar_t__ u8 ;
struct vf_pf_resc_request {scalar_t__ num_rxqs; scalar_t__ num_txqs; scalar_t__ num_sbs; scalar_t__ num_mac_filters; scalar_t__ num_vlan_filters; } ;
struct bnx2x_virtf {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ bnx2x_vf_max_queue_cnt (struct bnx2x*,struct bnx2x_virtf*) ; 
 scalar_t__ vf_mac_rules_cnt (struct bnx2x_virtf*) ; 
 scalar_t__ vf_rxq_count (struct bnx2x_virtf*) ; 
 scalar_t__ vf_sb_count (struct bnx2x_virtf*) ; 
 scalar_t__ vf_txq_count (struct bnx2x_virtf*) ; 
 scalar_t__ vf_vlan_rules_cnt (struct bnx2x_virtf*) ; 

__attribute__((used)) static
int bnx2x_vf_chk_avail_resc(struct bnx2x *bp, struct bnx2x_virtf *vf,
			    struct vf_pf_resc_request *req_resc)
{
	u8 rxq_cnt = vf_rxq_count(vf) ? : bnx2x_vf_max_queue_cnt(bp, vf);
	u8 txq_cnt = vf_txq_count(vf) ? : bnx2x_vf_max_queue_cnt(bp, vf);

	return ((req_resc->num_rxqs <= rxq_cnt) &&
		(req_resc->num_txqs <= txq_cnt) &&
		(req_resc->num_sbs <= vf_sb_count(vf))   &&
		(req_resc->num_mac_filters <= vf_mac_rules_cnt(vf)) &&
		(req_resc->num_vlan_filters <= vf_vlan_rules_cnt(vf)));
}