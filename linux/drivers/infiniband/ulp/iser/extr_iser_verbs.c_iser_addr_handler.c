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
struct rdma_cm_id {scalar_t__ context; } ;
struct iser_device {TYPE_2__* ib_device; } ;
struct ib_conn {int pi_support; struct iser_device* device; } ;
struct iser_conn {scalar_t__ state; struct ib_conn ib_conn; } ;
struct TYPE_3__ {int device_cap_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ attrs; } ;

/* Variables and functions */
 int IB_DEVICE_INTEGRITY_HANDOVER ; 
 scalar_t__ ISER_CONN_PENDING ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iser_calc_scsi_params (struct iser_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_connect_error (struct rdma_cm_id*) ; 
 struct iser_device* iser_device_find_by_ib_device (struct rdma_cm_id*) ; 
 int /*<<< orphan*/  iser_err (char*,...) ; 
 int /*<<< orphan*/  iser_max_sectors ; 
 scalar_t__ iser_pi_enable ; 
 int /*<<< orphan*/  iser_warn (char*,int /*<<< orphan*/ ) ; 
 int rdma_resolve_route (struct rdma_cm_id*,int) ; 

__attribute__((used)) static void iser_addr_handler(struct rdma_cm_id *cma_id)
{
	struct iser_device *device;
	struct iser_conn   *iser_conn;
	struct ib_conn   *ib_conn;
	int    ret;

	iser_conn = (struct iser_conn *)cma_id->context;
	if (iser_conn->state != ISER_CONN_PENDING)
		/* bailout */
		return;

	ib_conn = &iser_conn->ib_conn;
	device = iser_device_find_by_ib_device(cma_id);
	if (!device) {
		iser_err("device lookup/creation failed\n");
		iser_connect_error(cma_id);
		return;
	}

	ib_conn->device = device;

	/* connection T10-PI support */
	if (iser_pi_enable) {
		if (!(device->ib_device->attrs.device_cap_flags &
		      IB_DEVICE_INTEGRITY_HANDOVER)) {
			iser_warn("T10-PI requested but not supported on %s, "
				  "continue without T10-PI\n",
				  dev_name(&ib_conn->device->ib_device->dev));
			ib_conn->pi_support = false;
		} else {
			ib_conn->pi_support = true;
		}
	}

	iser_calc_scsi_params(iser_conn, iser_max_sectors);

	ret = rdma_resolve_route(cma_id, 1000);
	if (ret) {
		iser_err("resolve route failed: %d\n", ret);
		iser_connect_error(cma_id);
		return;
	}
}