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
typedef  int /*<<< orphan*/  u8 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct ocrdma_grh {int /*<<< orphan*/ * dgid; int /*<<< orphan*/  tclass_flow; int /*<<< orphan*/  pdid_hoplimit; } ;
struct ocrdma_eth_vlan {int dummy; } ;
struct ocrdma_eth_basic {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vlan_tag; } ;
struct ocrdma_av {int valid; TYPE_1__ eth_hdr; } ;
struct ocrdma_ah {int /*<<< orphan*/  sgid_index; struct ocrdma_av* av; } ;
struct ib_ah {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int OCRDMA_AV_VALID ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct ocrdma_ah* get_ocrdma_ah (struct ib_ah*) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (struct rdma_ah_attr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int) ; 

int ocrdma_query_ah(struct ib_ah *ibah, struct rdma_ah_attr *attr)
{
	struct ocrdma_ah *ah = get_ocrdma_ah(ibah);
	struct ocrdma_av *av = ah->av;
	struct ocrdma_grh *grh;

	attr->type = ibah->type;
	if (ah->av->valid & OCRDMA_AV_VALID) {
		grh = (struct ocrdma_grh *)((u8 *)ah->av +
				sizeof(struct ocrdma_eth_vlan));
		rdma_ah_set_sl(attr, be16_to_cpu(av->eth_hdr.vlan_tag) >> 13);
	} else {
		grh = (struct ocrdma_grh *)((u8 *)ah->av +
					sizeof(struct ocrdma_eth_basic));
		rdma_ah_set_sl(attr, 0);
	}
	rdma_ah_set_grh(attr, NULL,
			be32_to_cpu(grh->tclass_flow) & 0xffffffff,
			ah->sgid_index,
			be32_to_cpu(grh->pdid_hoplimit) & 0xff,
			be32_to_cpu(grh->tclass_flow) >> 24);
	rdma_ah_set_dgid_raw(attr, &grh->dgid[0]);
	return 0;
}