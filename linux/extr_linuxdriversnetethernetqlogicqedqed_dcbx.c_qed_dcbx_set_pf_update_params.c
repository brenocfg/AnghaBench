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
typedef  void* u8 ;
struct qed_dcbx_results {TYPE_1__* arr; } ;
struct protocol_dcb_data {int dummy; } ;
struct pf_update_ramrod_data {struct protocol_dcb_data eth_dcb_data; struct protocol_dcb_data iscsi_dcb_data; struct protocol_dcb_data rroce_dcb_data; struct protocol_dcb_data roce_dcb_data; struct protocol_dcb_data fcoe_dcb_data; void* update_eth_dcb_data_mode; void* update_iscsi_dcb_data_mode; void* update_rroce_dcb_data_mode; void* update_roce_dcb_data_mode; void* update_fcoe_dcb_data_mode; } ;
struct TYPE_2__ {void* update; } ;

/* Variables and functions */
 size_t DCBX_PROTOCOL_ETH ; 
 size_t DCBX_PROTOCOL_FCOE ; 
 size_t DCBX_PROTOCOL_ISCSI ; 
 size_t DCBX_PROTOCOL_ROCE ; 
 size_t DCBX_PROTOCOL_ROCE_V2 ; 
 int /*<<< orphan*/  qed_dcbx_update_protocol_data (struct protocol_dcb_data*,struct qed_dcbx_results*,size_t) ; 

void qed_dcbx_set_pf_update_params(struct qed_dcbx_results *p_src,
				   struct pf_update_ramrod_data *p_dest)
{
	struct protocol_dcb_data *p_dcb_data;
	u8 update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_FCOE].update;
	p_dest->update_fcoe_dcb_data_mode = update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_ROCE].update;
	p_dest->update_roce_dcb_data_mode = update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_ROCE_V2].update;
	p_dest->update_rroce_dcb_data_mode = update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_ISCSI].update;
	p_dest->update_iscsi_dcb_data_mode = update_flag;
	update_flag = p_src->arr[DCBX_PROTOCOL_ETH].update;
	p_dest->update_eth_dcb_data_mode = update_flag;

	p_dcb_data = &p_dest->fcoe_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_FCOE);
	p_dcb_data = &p_dest->roce_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ROCE);
	p_dcb_data = &p_dest->rroce_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ROCE_V2);
	p_dcb_data = &p_dest->iscsi_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ISCSI);
	p_dcb_data = &p_dest->eth_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ETH);
}