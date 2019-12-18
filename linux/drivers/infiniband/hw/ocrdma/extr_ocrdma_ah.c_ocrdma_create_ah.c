#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {struct ib_gid_attr* sgid_attr; } ;
struct rdma_ah_attr {scalar_t__ type; TYPE_1__ grh; } ;
struct ocrdma_pd {TYPE_3__* uctx; int /*<<< orphan*/  id; } ;
struct ocrdma_dev {int /*<<< orphan*/  update_sl; } ;
struct ocrdma_ah {int id; scalar_t__ hdr_type; } ;
struct ib_udata {int dummy; } ;
struct ib_gid_attr {int /*<<< orphan*/  gid; } ;
struct ib_ah {int /*<<< orphan*/  device; int /*<<< orphan*/  pd; } ;
struct TYPE_5__ {int* va; } ;
struct TYPE_6__ {TYPE_2__ ah_tbl; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_AH_GRH ; 
 int OCRDMA_AH_ID_MASK ; 
 int OCRDMA_AH_L3_TYPE_MASK ; 
 int OCRDMA_AH_L3_TYPE_SHIFT ; 
 int OCRDMA_AH_VLAN_VALID_MASK ; 
 int OCRDMA_AH_VLAN_VALID_SHIFT ; 
 scalar_t__ RDMA_AH_ATTR_TYPE_ROCE ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct ocrdma_ah* get_ocrdma_ah (struct ib_ah*) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 struct ocrdma_pd* get_ocrdma_pd (int /*<<< orphan*/ ) ; 
 int ocrdma_alloc_av (struct ocrdma_dev*,struct ocrdma_ah*) ; 
 int /*<<< orphan*/  ocrdma_free_av (struct ocrdma_dev*,struct ocrdma_ah*) ; 
 int /*<<< orphan*/  ocrdma_init_service_level (struct ocrdma_dev*) ; 
 scalar_t__ ocrdma_is_udp_encap_supported (struct ocrdma_dev*) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 scalar_t__ rdma_gid_attr_network_type (struct ib_gid_attr const*) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,int*,int /*<<< orphan*/ *) ; 
 int set_av_attr (struct ocrdma_dev*,struct ocrdma_ah*,struct rdma_ah_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

int ocrdma_create_ah(struct ib_ah *ibah, struct rdma_ah_attr *attr, u32 flags,
		     struct ib_udata *udata)
{
	u32 *ahid_addr;
	int status;
	struct ocrdma_ah *ah = get_ocrdma_ah(ibah);
	bool isvlan = false;
	u16 vlan_tag = 0xffff;
	const struct ib_gid_attr *sgid_attr;
	struct ocrdma_pd *pd = get_ocrdma_pd(ibah->pd);
	struct ocrdma_dev *dev = get_ocrdma_dev(ibah->device);

	if ((attr->type != RDMA_AH_ATTR_TYPE_ROCE) ||
	    !(rdma_ah_get_ah_flags(attr) & IB_AH_GRH))
		return -EINVAL;

	if (atomic_cmpxchg(&dev->update_sl, 1, 0))
		ocrdma_init_service_level(dev);

	sgid_attr = attr->grh.sgid_attr;
	status = rdma_read_gid_l2_fields(sgid_attr, &vlan_tag, NULL);
	if (status)
		return status;

	status = ocrdma_alloc_av(dev, ah);
	if (status)
		goto av_err;

	/* Get network header type for this GID */
	ah->hdr_type = rdma_gid_attr_network_type(sgid_attr);

	status = set_av_attr(dev, ah, attr, &sgid_attr->gid, pd->id,
			     &isvlan, vlan_tag);
	if (status)
		goto av_conf_err;

	/* if pd is for the user process, pass the ah_id to user space */
	if ((pd->uctx) && (pd->uctx->ah_tbl.va)) {
		ahid_addr = pd->uctx->ah_tbl.va + rdma_ah_get_dlid(attr);
		*ahid_addr = 0;
		*ahid_addr |= ah->id & OCRDMA_AH_ID_MASK;
		if (ocrdma_is_udp_encap_supported(dev)) {
			*ahid_addr |= ((u32)ah->hdr_type &
				       OCRDMA_AH_L3_TYPE_MASK) <<
				       OCRDMA_AH_L3_TYPE_SHIFT;
		}
		if (isvlan)
			*ahid_addr |= (OCRDMA_AH_VLAN_VALID_MASK <<
				       OCRDMA_AH_VLAN_VALID_SHIFT);
	}

	return 0;

av_conf_err:
	ocrdma_free_av(dev, ah);
av_err:
	return status;
}