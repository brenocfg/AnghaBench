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
typedef  int u64 ;
struct i40iw_sc_vsi {TYPE_1__* qos; } ;
struct i40iw_sc_cqp {scalar_t__ polarity; int /*<<< orphan*/  dev; } ;
struct i40iw_qhash_table_info {int* mac_addr; scalar_t__ qp_num; scalar_t__ dest_port; scalar_t__ ipv4_valid; scalar_t__* dest_ip; size_t user_pri; scalar_t__ vlan_valid; scalar_t__ vlan_id; scalar_t__ entry_type; scalar_t__ src_port; scalar_t__* src_ip; scalar_t__ manage; struct i40iw_sc_vsi* vsi; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;
struct TYPE_2__ {scalar_t__ qs_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_ADDR0 ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_ADDR1 ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_ADDR2 ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_ADDR3 ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_DEST_PORT ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_ENTRYTYPE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_IPV4VALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_MANAGE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_OPCODE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_QPN ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_QS_HANDLE ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_SRC_PORT ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_VLANID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_VLANVALID ; 
 int /*<<< orphan*/  I40IW_CQPSQ_QHASH_WQEVALID ; 
 scalar_t__ I40IW_CQP_OP_MANAGE_QUAD_HASH_TABLE_ENTRY ; 
 int I40IW_CQP_WQE_SIZE ; 
 int /*<<< orphan*/  I40IW_DEBUG_WQE ; 
 int I40IW_ERR_RING_FULL ; 
 scalar_t__ I40IW_QHASH_TYPE_TCP_ESTABLISHED ; 
 int LS_64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int LS_64_1 (int,int) ; 
 int /*<<< orphan*/  i40iw_debug_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  i40iw_insert_wqe_hdr (int*,int) ; 
 int* i40iw_sc_cqp_get_next_send_wqe (struct i40iw_sc_cqp*,int) ; 
 int /*<<< orphan*/  i40iw_sc_cqp_post_sq (struct i40iw_sc_cqp*) ; 
 int /*<<< orphan*/  set_64bit_val (int*,int,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_manage_qhash_table_entry(
					struct i40iw_sc_cqp *cqp,
					struct i40iw_qhash_table_info *info,
					u64 scratch,
					bool post_sq)
{
	u64 *wqe;
	u64 qw1 = 0;
	u64 qw2 = 0;
	u64 temp;
	struct i40iw_sc_vsi *vsi = info->vsi;

	wqe = i40iw_sc_cqp_get_next_send_wqe(cqp, scratch);
	if (!wqe)
		return I40IW_ERR_RING_FULL;

	temp = info->mac_addr[5] |
		LS_64_1(info->mac_addr[4], 8) |
		LS_64_1(info->mac_addr[3], 16) |
		LS_64_1(info->mac_addr[2], 24) |
		LS_64_1(info->mac_addr[1], 32) |
		LS_64_1(info->mac_addr[0], 40);

	set_64bit_val(wqe, 0, temp);

	qw1 = LS_64(info->qp_num, I40IW_CQPSQ_QHASH_QPN) |
	      LS_64(info->dest_port, I40IW_CQPSQ_QHASH_DEST_PORT);
	if (info->ipv4_valid) {
		set_64bit_val(wqe,
			      48,
			      LS_64(info->dest_ip[0], I40IW_CQPSQ_QHASH_ADDR3));
	} else {
		set_64bit_val(wqe,
			      56,
			      LS_64(info->dest_ip[0], I40IW_CQPSQ_QHASH_ADDR0) |
			      LS_64(info->dest_ip[1], I40IW_CQPSQ_QHASH_ADDR1));

		set_64bit_val(wqe,
			      48,
			      LS_64(info->dest_ip[2], I40IW_CQPSQ_QHASH_ADDR2) |
			      LS_64(info->dest_ip[3], I40IW_CQPSQ_QHASH_ADDR3));
	}
	qw2 = LS_64(vsi->qos[info->user_pri].qs_handle, I40IW_CQPSQ_QHASH_QS_HANDLE);
	if (info->vlan_valid)
		qw2 |= LS_64(info->vlan_id, I40IW_CQPSQ_QHASH_VLANID);
	set_64bit_val(wqe, 16, qw2);
	if (info->entry_type == I40IW_QHASH_TYPE_TCP_ESTABLISHED) {
		qw1 |= LS_64(info->src_port, I40IW_CQPSQ_QHASH_SRC_PORT);
		if (!info->ipv4_valid) {
			set_64bit_val(wqe,
				      40,
				      LS_64(info->src_ip[0], I40IW_CQPSQ_QHASH_ADDR0) |
				      LS_64(info->src_ip[1], I40IW_CQPSQ_QHASH_ADDR1));
			set_64bit_val(wqe,
				      32,
				      LS_64(info->src_ip[2], I40IW_CQPSQ_QHASH_ADDR2) |
				      LS_64(info->src_ip[3], I40IW_CQPSQ_QHASH_ADDR3));
		} else {
			set_64bit_val(wqe,
				      32,
				      LS_64(info->src_ip[0], I40IW_CQPSQ_QHASH_ADDR3));
		}
	}

	set_64bit_val(wqe, 8, qw1);
	temp = LS_64(cqp->polarity, I40IW_CQPSQ_QHASH_WQEVALID) |
	       LS_64(I40IW_CQP_OP_MANAGE_QUAD_HASH_TABLE_ENTRY, I40IW_CQPSQ_QHASH_OPCODE) |
	       LS_64(info->manage, I40IW_CQPSQ_QHASH_MANAGE) |
	       LS_64(info->ipv4_valid, I40IW_CQPSQ_QHASH_IPV4VALID) |
	       LS_64(info->vlan_valid, I40IW_CQPSQ_QHASH_VLANVALID) |
	       LS_64(info->entry_type, I40IW_CQPSQ_QHASH_ENTRYTYPE);

	i40iw_insert_wqe_hdr(wqe, temp);

	i40iw_debug_buf(cqp->dev, I40IW_DEBUG_WQE, "MANAGE_QHASH WQE",
			wqe, I40IW_CQP_WQE_SIZE * 8);

	if (post_sq)
		i40iw_sc_cqp_post_sq(cqp);
	return 0;
}