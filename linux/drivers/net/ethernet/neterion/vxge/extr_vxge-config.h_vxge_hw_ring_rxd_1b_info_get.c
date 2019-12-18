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
typedef  void* u32 ;
struct vxge_hw_ring_rxd_info {void* rth_value; void* rth_hash_type; void* rth_spdm_hit; void* rth_it_hit; void* rth_bucket; void* vlan; void* is_vlan; void* proto; void* frame; void* l4_cksum; void* l4_cksum_valid; void* l3_cksum; void* l3_cksum_valid; void* fast_path_eligible; void* is_icmp; void* syn_flag; } ;
struct vxge_hw_ring_rxd_1 {int /*<<< orphan*/  control_1; int /*<<< orphan*/  control_0; } ;
struct __vxge_hw_ring {int dummy; } ;

/* Variables and functions */
 scalar_t__ VXGE_HW_RING_RXD_1_RTH_HASH_VAL_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_ETHER_ENCAP_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_FAST_PATH_ELIGIBLE_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_FRAME_PROTO_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_IS_ICMP_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_IS_VLAN_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_L3_CKSUM_CORRECT_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_L3_CKSUM_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_L4_CKSUM_CORRECT_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_L4_CKSUM_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_RTH_BUCKET_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_RTH_HASH_TYPE_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_RTH_IT_HIT_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_RTH_SPDM_HIT_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_SYN_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ VXGE_HW_RING_RXD_VLAN_TAG_GET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void vxge_hw_ring_rxd_1b_info_get(
	struct __vxge_hw_ring *ring_handle,
	void *rxdh,
	struct vxge_hw_ring_rxd_info *rxd_info)
{

	struct vxge_hw_ring_rxd_1 *rxdp = (struct vxge_hw_ring_rxd_1 *)rxdh;
	rxd_info->syn_flag =
		(u32)VXGE_HW_RING_RXD_SYN_GET(rxdp->control_0);
	rxd_info->is_icmp =
		(u32)VXGE_HW_RING_RXD_IS_ICMP_GET(rxdp->control_0);
	rxd_info->fast_path_eligible =
		(u32)VXGE_HW_RING_RXD_FAST_PATH_ELIGIBLE_GET(rxdp->control_0);
	rxd_info->l3_cksum_valid =
		(u32)VXGE_HW_RING_RXD_L3_CKSUM_CORRECT_GET(rxdp->control_0);
	rxd_info->l3_cksum =
		(u32)VXGE_HW_RING_RXD_L3_CKSUM_GET(rxdp->control_0);
	rxd_info->l4_cksum_valid =
		(u32)VXGE_HW_RING_RXD_L4_CKSUM_CORRECT_GET(rxdp->control_0);
	rxd_info->l4_cksum =
		(u32)VXGE_HW_RING_RXD_L4_CKSUM_GET(rxdp->control_0);
	rxd_info->frame =
		(u32)VXGE_HW_RING_RXD_ETHER_ENCAP_GET(rxdp->control_0);
	rxd_info->proto =
		(u32)VXGE_HW_RING_RXD_FRAME_PROTO_GET(rxdp->control_0);
	rxd_info->is_vlan =
		(u32)VXGE_HW_RING_RXD_IS_VLAN_GET(rxdp->control_0);
	rxd_info->vlan =
		(u32)VXGE_HW_RING_RXD_VLAN_TAG_GET(rxdp->control_1);
	rxd_info->rth_bucket =
		(u32)VXGE_HW_RING_RXD_RTH_BUCKET_GET(rxdp->control_0);
	rxd_info->rth_it_hit =
		(u32)VXGE_HW_RING_RXD_RTH_IT_HIT_GET(rxdp->control_0);
	rxd_info->rth_spdm_hit =
		(u32)VXGE_HW_RING_RXD_RTH_SPDM_HIT_GET(rxdp->control_0);
	rxd_info->rth_hash_type =
		(u32)VXGE_HW_RING_RXD_RTH_HASH_TYPE_GET(rxdp->control_0);
	rxd_info->rth_value =
		(u32)VXGE_HW_RING_RXD_1_RTH_HASH_VAL_GET(rxdp->control_1);
}