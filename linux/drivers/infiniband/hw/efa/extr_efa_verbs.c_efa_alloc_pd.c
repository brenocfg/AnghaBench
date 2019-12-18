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
struct ib_udata {scalar_t__ outlen; scalar_t__ inlen; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct efa_pd {int /*<<< orphan*/  pdn; } ;
struct efa_ibv_alloc_pd_resp {int /*<<< orphan*/  pdn; } ;
struct TYPE_3__ {int /*<<< orphan*/  alloc_pd_err; } ;
struct TYPE_4__ {TYPE_1__ sw_stats; } ;
struct efa_dev {TYPE_2__ stats; int /*<<< orphan*/  ibdev; int /*<<< orphan*/  edev; } ;
struct efa_com_alloc_pd_result {int /*<<< orphan*/  pdn; } ;
typedef  int /*<<< orphan*/  resp ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int efa_com_alloc_pd (int /*<<< orphan*/ *,struct efa_com_alloc_pd_result*) ; 
 int /*<<< orphan*/  efa_pd_dealloc (struct efa_dev*,int /*<<< orphan*/ ) ; 
 int ib_copy_to_udata (struct ib_udata*,struct efa_ibv_alloc_pd_resp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_is_udata_cleared (struct ib_udata*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  min (int,scalar_t__) ; 
 struct efa_dev* to_edev (int /*<<< orphan*/ ) ; 
 struct efa_pd* to_epd (struct ib_pd*) ; 

int efa_alloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct efa_dev *dev = to_edev(ibpd->device);
	struct efa_ibv_alloc_pd_resp resp = {};
	struct efa_com_alloc_pd_result result;
	struct efa_pd *pd = to_epd(ibpd);
	int err;

	if (udata->inlen &&
	    !ib_is_udata_cleared(udata, 0, udata->inlen)) {
		ibdev_dbg(&dev->ibdev,
			  "Incompatible ABI params, udata not cleared\n");
		err = -EINVAL;
		goto err_out;
	}

	err = efa_com_alloc_pd(&dev->edev, &result);
	if (err)
		goto err_out;

	pd->pdn = result.pdn;
	resp.pdn = result.pdn;

	if (udata->outlen) {
		err = ib_copy_to_udata(udata, &resp,
				       min(sizeof(resp), udata->outlen));
		if (err) {
			ibdev_dbg(&dev->ibdev,
				  "Failed to copy udata for alloc_pd\n");
			goto err_dealloc_pd;
		}
	}

	ibdev_dbg(&dev->ibdev, "Allocated pd[%d]\n", pd->pdn);

	return 0;

err_dealloc_pd:
	efa_pd_dealloc(dev, result.pdn);
err_out:
	atomic64_inc(&dev->stats.sw_stats.alloc_pd_err);
	return err;
}