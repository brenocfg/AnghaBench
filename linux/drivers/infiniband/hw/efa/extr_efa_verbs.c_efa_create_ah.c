#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  raw; } ;
struct TYPE_7__ {TYPE_1__ dgid; } ;
struct rdma_ah_attr {TYPE_2__ grh; } ;
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_ah {int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;
struct efa_ibv_create_ah_resp {int /*<<< orphan*/  efa_address_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  create_ah_err; } ;
struct TYPE_9__ {TYPE_3__ sw_stats; } ;
struct efa_dev {TYPE_4__ stats; int /*<<< orphan*/  ibdev; int /*<<< orphan*/  edev; } ;
struct efa_com_create_ah_result {int /*<<< orphan*/  ah; } ;
struct efa_com_create_ah_params {int /*<<< orphan*/  pdn; int /*<<< orphan*/  dest_addr; } ;
struct efa_ah {int /*<<< orphan*/  ah; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  resp ;
struct TYPE_10__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int RDMA_CREATE_AH_SLEEPABLE ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efa_ah_destroy (struct efa_dev*,struct efa_ah*) ; 
 int efa_com_create_ah (int /*<<< orphan*/ *,struct efa_com_create_ah_params*,struct efa_com_create_ah_result*) ; 
 int ib_copy_to_udata (struct ib_udata*,struct efa_ibv_create_ah_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_is_udata_cleared (struct ib_udata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,scalar_t__) ; 
 struct efa_ah* to_eah (struct ib_ah*) ; 
 struct efa_dev* to_edev (int /*<<< orphan*/ ) ; 
 TYPE_5__* to_epd (int /*<<< orphan*/ ) ; 

int efa_create_ah(struct ib_ah *ibah,
		  struct rdma_ah_attr *ah_attr,
		  u32 flags,
		  struct ib_udata *udata)
{
	struct efa_dev *dev = to_edev(ibah->device);
	struct efa_com_create_ah_params params = {};
	struct efa_ibv_create_ah_resp resp = {};
	struct efa_com_create_ah_result result;
	struct efa_ah *ah = to_eah(ibah);
	int err;

	if (!(flags & RDMA_CREATE_AH_SLEEPABLE)) {
		ibdev_dbg(&dev->ibdev,
			  "Create address handle is not supported in atomic context\n");
		err = -EOPNOTSUPP;
		goto err_out;
	}

	if (udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) {
		ibdev_dbg(&dev->ibdev, "Incompatible ABI params\n");
		err = -EINVAL;
		goto err_out;
	}

	memcpy(params.dest_addr, ah_attr->grh.dgid.raw,
	       sizeof(params.dest_addr));
	params.pdn = to_epd(ibah->pd)->pdn;
	err = efa_com_create_ah(&dev->edev, &params, &result);
	if (err)
		goto err_out;

	memcpy(ah->id, ah_attr->grh.dgid.raw, sizeof(ah->id));
	ah->ah = result.ah;

	resp.efa_address_handle = result.ah;

	if (udata->outlen) {
		err = ib_copy_to_udata(udata, &resp,
				       min(sizeof(resp), udata->outlen));
		if (err) {
			ibdev_dbg(&dev->ibdev,
				  "Failed to copy udata for create_ah response\n");
			goto err_destroy_ah;
		}
	}
	ibdev_dbg(&dev->ibdev, "Created ah[%d]\n", ah->ah);

	return 0;

err_destroy_ah:
	efa_ah_destroy(dev, ah);
err_out:
	atomic64_inc(&dev->stats.sw_stats.create_ah_err);
	return err;
}