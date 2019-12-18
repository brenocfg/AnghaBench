#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rdma_conn_param {int initiator_depth; int retry_count; int rnr_retry_count; int private_data_len; void* private_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  responder_resources; } ;
struct rdma_cm_id {scalar_t__ context; } ;
struct iser_device {int /*<<< orphan*/  remote_inv_sup; TYPE_2__* ib_device; } ;
struct ib_conn {struct iser_device* device; } ;
struct iser_conn {scalar_t__ state; struct ib_conn ib_conn; } ;
struct iser_cm_hdr {int initiator_depth; int retry_count; int rnr_retry_count; int private_data_len; void* private_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  responder_resources; } ;
typedef  int /*<<< orphan*/  req_hdr ;
struct TYPE_3__ {int /*<<< orphan*/  max_qp_rd_atom; } ;
struct TYPE_4__ {TYPE_1__ attrs; } ;

/* Variables and functions */
 scalar_t__ ISER_CONN_PENDING ; 
 int /*<<< orphan*/  ISER_SEND_W_INV_NOT_SUP ; 
 int /*<<< orphan*/  ISER_ZBVA_NOT_SUP ; 
 int /*<<< orphan*/  iser_connect_error (struct rdma_cm_id*) ; 
 int iser_create_ib_conn_res (struct ib_conn*) ; 
 int /*<<< orphan*/  iser_err (char*,int) ; 
 int /*<<< orphan*/  memset (struct rdma_conn_param*,int /*<<< orphan*/ ,int) ; 
 int rdma_connect (struct rdma_cm_id*,struct rdma_conn_param*) ; 

__attribute__((used)) static void iser_route_handler(struct rdma_cm_id *cma_id)
{
	struct rdma_conn_param conn_param;
	int    ret;
	struct iser_cm_hdr req_hdr;
	struct iser_conn *iser_conn = (struct iser_conn *)cma_id->context;
	struct ib_conn *ib_conn = &iser_conn->ib_conn;
	struct iser_device *device = ib_conn->device;

	if (iser_conn->state != ISER_CONN_PENDING)
		/* bailout */
		return;

	ret = iser_create_ib_conn_res(ib_conn);
	if (ret)
		goto failure;

	memset(&conn_param, 0, sizeof conn_param);
	conn_param.responder_resources = device->ib_device->attrs.max_qp_rd_atom;
	conn_param.initiator_depth     = 1;
	conn_param.retry_count	       = 7;
	conn_param.rnr_retry_count     = 6;

	memset(&req_hdr, 0, sizeof(req_hdr));
	req_hdr.flags = ISER_ZBVA_NOT_SUP;
	if (!device->remote_inv_sup)
		req_hdr.flags |= ISER_SEND_W_INV_NOT_SUP;
	conn_param.private_data	= (void *)&req_hdr;
	conn_param.private_data_len = sizeof(struct iser_cm_hdr);

	ret = rdma_connect(cma_id, &conn_param);
	if (ret) {
		iser_err("failure connecting: %d\n", ret);
		goto failure;
	}

	return;
failure:
	iser_connect_error(cma_id);
}