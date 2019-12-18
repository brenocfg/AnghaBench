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
struct ib_udata {int dummy; } ;
struct ib_mr {int /*<<< orphan*/  lkey; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  lkey; } ;
struct efa_mr {int /*<<< orphan*/  umem; TYPE_1__ ibmr; } ;
struct efa_dev {int /*<<< orphan*/  edev; int /*<<< orphan*/  ibdev; } ;
struct efa_com_dereg_mr_params {int /*<<< orphan*/  l_key; } ;

/* Variables and functions */
 int efa_com_dereg_mr (int /*<<< orphan*/ *,struct efa_com_dereg_mr_params*) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct efa_mr*) ; 
 struct efa_dev* to_edev (int /*<<< orphan*/ ) ; 
 struct efa_mr* to_emr (struct ib_mr*) ; 

int efa_dereg_mr(struct ib_mr *ibmr, struct ib_udata *udata)
{
	struct efa_dev *dev = to_edev(ibmr->device);
	struct efa_com_dereg_mr_params params;
	struct efa_mr *mr = to_emr(ibmr);
	int err;

	ibdev_dbg(&dev->ibdev, "Deregister mr[%d]\n", ibmr->lkey);

	params.l_key = mr->ibmr.lkey;
	err = efa_com_dereg_mr(&dev->edev, &params);
	if (err)
		return err;

	ib_umem_release(mr->umem);
	kfree(mr);

	return 0;
}