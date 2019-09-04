#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  placement_offset; TYPE_4__ opaque_data; int /*<<< orphan*/  vlan; int /*<<< orphan*/  packet_length; TYPE_2__ err_flags; TYPE_1__ parse_flags; } ;
union core_rx_cqe_union {TYPE_6__ rx_cqe_fp; } ;
struct TYPE_11__ {int /*<<< orphan*/  placement_offset; } ;
struct TYPE_9__ {void* packet_length; } ;
struct qed_ll2_comp_rx_data {TYPE_5__ u; void* opaque_data_1; void* opaque_data_0; void* vlan; TYPE_3__ length; void* err_flags; void* parse_flags; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_ll2_rxq_parse_reg(struct qed_hwfn *p_hwfn,
				  union core_rx_cqe_union *p_cqe,
				  struct qed_ll2_comp_rx_data *data)
{
	data->parse_flags = le16_to_cpu(p_cqe->rx_cqe_fp.parse_flags.flags);
	data->err_flags = le16_to_cpu(p_cqe->rx_cqe_fp.err_flags.flags);
	data->length.packet_length =
	    le16_to_cpu(p_cqe->rx_cqe_fp.packet_length);
	data->vlan = le16_to_cpu(p_cqe->rx_cqe_fp.vlan);
	data->opaque_data_0 = le32_to_cpu(p_cqe->rx_cqe_fp.opaque_data.data[0]);
	data->opaque_data_1 = le32_to_cpu(p_cqe->rx_cqe_fp.opaque_data.data[1]);
	data->u.placement_offset = p_cqe->rx_cqe_fp.placement_offset;
}