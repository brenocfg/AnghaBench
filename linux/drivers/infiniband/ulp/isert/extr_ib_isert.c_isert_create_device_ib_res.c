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
struct isert_device {int pi_capable; int /*<<< orphan*/  pd; struct ib_device* ib_device; } ;
struct TYPE_2__ {int device_cap_flags; int /*<<< orphan*/  max_sge_rd; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; } ;
struct ib_device {TYPE_1__ attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_DEVICE_INTEGRITY_HANDOVER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_alloc_pd (struct ib_device*,int /*<<< orphan*/ ) ; 
 int isert_alloc_comps (struct isert_device*) ; 
 int /*<<< orphan*/  isert_dbg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  isert_err (char*,struct isert_device*,int) ; 
 int /*<<< orphan*/  isert_free_comps (struct isert_device*) ; 

__attribute__((used)) static int
isert_create_device_ib_res(struct isert_device *device)
{
	struct ib_device *ib_dev = device->ib_device;
	int ret;

	isert_dbg("devattr->max_send_sge: %d devattr->max_recv_sge %d\n",
		  ib_dev->attrs.max_send_sge, ib_dev->attrs.max_recv_sge);
	isert_dbg("devattr->max_sge_rd: %d\n", ib_dev->attrs.max_sge_rd);

	ret = isert_alloc_comps(device);
	if (ret)
		goto out;

	device->pd = ib_alloc_pd(ib_dev, 0);
	if (IS_ERR(device->pd)) {
		ret = PTR_ERR(device->pd);
		isert_err("failed to allocate pd, device %p, ret=%d\n",
			  device, ret);
		goto out_cq;
	}

	/* Check signature cap */
	device->pi_capable = ib_dev->attrs.device_cap_flags &
			     IB_DEVICE_INTEGRITY_HANDOVER ? true : false;

	return 0;

out_cq:
	isert_free_comps(device);
out:
	if (ret > 0)
		ret = -EINVAL;
	return ret;
}