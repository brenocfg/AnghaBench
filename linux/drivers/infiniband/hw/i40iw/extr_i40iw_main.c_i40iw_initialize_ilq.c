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
struct i40iw_puda_rsrc_info {int cq_id; int count; int pd_id; int sq_size; int rq_size; int buf_size; int tx_buf_cnt; int /*<<< orphan*/  xmit_complete; int /*<<< orphan*/  receive; scalar_t__ qp_id; int /*<<< orphan*/  type; } ;
struct i40iw_device {int /*<<< orphan*/  vsi; } ;
typedef  int /*<<< orphan*/  info ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_PUDA_RSRC_TYPE_ILQ ; 
 int /*<<< orphan*/  i40iw_free_sqbuf ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 int i40iw_puda_create_rsrc (int /*<<< orphan*/ *,struct i40iw_puda_rsrc_info*) ; 
 int /*<<< orphan*/  i40iw_receive_ilq ; 
 int /*<<< orphan*/  memset (struct i40iw_puda_rsrc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_initialize_ilq(struct i40iw_device *iwdev)
{
	struct i40iw_puda_rsrc_info info;
	enum i40iw_status_code status;

	memset(&info, 0, sizeof(info));
	info.type = I40IW_PUDA_RSRC_TYPE_ILQ;
	info.cq_id = 1;
	info.qp_id = 0;
	info.count = 1;
	info.pd_id = 1;
	info.sq_size = 8192;
	info.rq_size = 8192;
	info.buf_size = 1024;
	info.tx_buf_cnt = 16384;
	info.receive = i40iw_receive_ilq;
	info.xmit_complete = i40iw_free_sqbuf;
	status = i40iw_puda_create_rsrc(&iwdev->vsi, &info);
	if (status)
		i40iw_pr_err("ilq create fail\n");
	return status;
}