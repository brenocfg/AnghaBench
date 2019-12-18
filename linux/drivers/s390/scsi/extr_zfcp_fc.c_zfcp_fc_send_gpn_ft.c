#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_ct_els {int /*<<< orphan*/ * resp; int /*<<< orphan*/ * req; int /*<<< orphan*/ * handler_data; int /*<<< orphan*/  handler; } ;
struct TYPE_7__ {int /*<<< orphan*/  fn_fc4_type; } ;
struct zfcp_fc_gpn_ft_req {TYPE_3__ gpn_ft; int /*<<< orphan*/  ct_hdr; } ;
struct TYPE_5__ {struct zfcp_fc_gpn_ft_req req; } ;
struct TYPE_6__ {TYPE_1__ gpn_ft; } ;
struct zfcp_fc_req {int /*<<< orphan*/  sg_rsp; int /*<<< orphan*/  sg_req; TYPE_2__ u; struct zfcp_fsf_ct_els ct_els; } ;
struct zfcp_adapter {TYPE_4__* gs; } ;
struct TYPE_8__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_NS_GPN_FT ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  ZFCP_FC_CTELS_TMO ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_complete ; 
 int /*<<< orphan*/  zfcp_fc_ct_ns_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int zfcp_fsf_send_ct (int /*<<< orphan*/ *,struct zfcp_fsf_ct_els*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_fc_send_gpn_ft(struct zfcp_fc_req *fc_req,
			       struct zfcp_adapter *adapter, int max_bytes)
{
	struct zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	struct zfcp_fc_gpn_ft_req *req = &fc_req->u.gpn_ft.req;
	DECLARE_COMPLETION_ONSTACK(completion);
	int ret;

	zfcp_fc_ct_ns_init(&req->ct_hdr, FC_NS_GPN_FT, max_bytes);
	req->gpn_ft.fn_fc4_type = FC_TYPE_FCP;

	ct_els->handler = zfcp_fc_complete;
	ct_els->handler_data = &completion;
	ct_els->req = &fc_req->sg_req;
	ct_els->resp = &fc_req->sg_rsp;

	ret = zfcp_fsf_send_ct(&adapter->gs->ds, ct_els, NULL,
			       ZFCP_FC_CTELS_TMO);
	if (!ret)
		wait_for_completion(&completion);
	return ret;
}