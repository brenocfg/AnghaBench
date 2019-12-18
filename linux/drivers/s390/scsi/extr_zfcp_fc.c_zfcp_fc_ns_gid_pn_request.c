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
struct zfcp_port {int /*<<< orphan*/  wwpn; struct zfcp_adapter* adapter; } ;
struct TYPE_12__ {int /*<<< orphan*/ * resp; int /*<<< orphan*/ * req; int /*<<< orphan*/ * handler_data; int /*<<< orphan*/  handler; struct zfcp_port* port; } ;
struct TYPE_9__ {int /*<<< orphan*/  fn_wwpn; } ;
struct zfcp_fc_gid_pn_rsp {TYPE_3__ gid_pn; int /*<<< orphan*/  ct_hdr; } ;
struct TYPE_7__ {struct zfcp_fc_gid_pn_rsp rsp; struct zfcp_fc_gid_pn_rsp req; } ;
struct TYPE_8__ {TYPE_1__ gid_pn; } ;
struct zfcp_fc_req {TYPE_6__ ct_els; int /*<<< orphan*/  sg_rsp; int /*<<< orphan*/  sg_req; TYPE_2__ u; } ;
struct zfcp_fc_gid_pn_req {TYPE_3__ gid_pn; int /*<<< orphan*/  ct_hdr; } ;
struct TYPE_11__ {int /*<<< orphan*/  gid_pn_req; } ;
struct zfcp_adapter {TYPE_5__ pool; TYPE_4__* gs; } ;
struct TYPE_10__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_NS_GID_PN ; 
 int /*<<< orphan*/  ZFCP_FC_CTELS_TMO ; 
 int /*<<< orphan*/  ZFCP_FC_CT_SIZE_PAGE ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,struct zfcp_fc_gid_pn_rsp*,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_complete ; 
 int /*<<< orphan*/  zfcp_fc_ct_ns_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_ns_gid_pn_eval (struct zfcp_fc_req*) ; 
 int zfcp_fsf_send_ct (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_fc_ns_gid_pn_request(struct zfcp_port *port,
				     struct zfcp_fc_req *fc_req)
{
	struct zfcp_adapter *adapter = port->adapter;
	DECLARE_COMPLETION_ONSTACK(completion);
	struct zfcp_fc_gid_pn_req *gid_pn_req = &fc_req->u.gid_pn.req;
	struct zfcp_fc_gid_pn_rsp *gid_pn_rsp = &fc_req->u.gid_pn.rsp;
	int ret;

	/* setup parameters for send generic command */
	fc_req->ct_els.port = port;
	fc_req->ct_els.handler = zfcp_fc_complete;
	fc_req->ct_els.handler_data = &completion;
	fc_req->ct_els.req = &fc_req->sg_req;
	fc_req->ct_els.resp = &fc_req->sg_rsp;
	sg_init_one(&fc_req->sg_req, gid_pn_req, sizeof(*gid_pn_req));
	sg_init_one(&fc_req->sg_rsp, gid_pn_rsp, sizeof(*gid_pn_rsp));

	zfcp_fc_ct_ns_init(&gid_pn_req->ct_hdr,
			   FC_NS_GID_PN, ZFCP_FC_CT_SIZE_PAGE);
	gid_pn_req->gid_pn.fn_wwpn = cpu_to_be64(port->wwpn);

	ret = zfcp_fsf_send_ct(&adapter->gs->ds, &fc_req->ct_els,
			       adapter->pool.gid_pn_req,
			       ZFCP_FC_CTELS_TMO);
	if (!ret) {
		wait_for_completion(&completion);
		zfcp_fc_ns_gid_pn_eval(fc_req);
	}
	return ret;
}