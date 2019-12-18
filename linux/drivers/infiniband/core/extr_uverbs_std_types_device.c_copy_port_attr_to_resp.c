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
typedef  int /*<<< orphan*/  u8 ;
struct ib_uverbs_query_port_resp {int /*<<< orphan*/  link_layer; int /*<<< orphan*/  phys_state; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; int /*<<< orphan*/  init_type_reply; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  max_vl_num; int /*<<< orphan*/  lmc; void* sm_lid; void* lid; int /*<<< orphan*/  flags; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; int /*<<< orphan*/  max_msg_sz; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  state; } ;
struct ib_port_attr {int /*<<< orphan*/  phys_state; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; int /*<<< orphan*/  init_type_reply; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  max_vl_num; int /*<<< orphan*/  lmc; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lid; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; int /*<<< orphan*/  max_msg_sz; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  state; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_UVERBS_QPF_GRH_REQUIRED ; 
 void* OPA_TO_IB_UCAST_LID (int /*<<< orphan*/ ) ; 
 void* ib_lid_cpu16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_port_cap_flags (struct ib_port_attr*) ; 
 scalar_t__ rdma_cap_opa_ah (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_is_grh_required (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_port_get_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 

void copy_port_attr_to_resp(struct ib_port_attr *attr,
			    struct ib_uverbs_query_port_resp *resp,
			    struct ib_device *ib_dev, u8 port_num)
{
	resp->state = attr->state;
	resp->max_mtu = attr->max_mtu;
	resp->active_mtu = attr->active_mtu;
	resp->gid_tbl_len = attr->gid_tbl_len;
	resp->port_cap_flags = make_port_cap_flags(attr);
	resp->max_msg_sz = attr->max_msg_sz;
	resp->bad_pkey_cntr = attr->bad_pkey_cntr;
	resp->qkey_viol_cntr = attr->qkey_viol_cntr;
	resp->pkey_tbl_len = attr->pkey_tbl_len;

	if (rdma_is_grh_required(ib_dev, port_num))
		resp->flags |= IB_UVERBS_QPF_GRH_REQUIRED;

	if (rdma_cap_opa_ah(ib_dev, port_num)) {
		resp->lid = OPA_TO_IB_UCAST_LID(attr->lid);
		resp->sm_lid = OPA_TO_IB_UCAST_LID(attr->sm_lid);
	} else {
		resp->lid = ib_lid_cpu16(attr->lid);
		resp->sm_lid = ib_lid_cpu16(attr->sm_lid);
	}

	resp->lmc = attr->lmc;
	resp->max_vl_num = attr->max_vl_num;
	resp->sm_sl = attr->sm_sl;
	resp->subnet_timeout = attr->subnet_timeout;
	resp->init_type_reply = attr->init_type_reply;
	resp->active_width = attr->active_width;
	resp->active_speed = attr->active_speed;
	resp->phys_state = attr->phys_state;
	resp->link_layer = rdma_port_get_link_layer(ib_dev, port_num);
}