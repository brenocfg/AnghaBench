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
typedef  int /*<<< orphan*/  uresp ;
typedef  int /*<<< orphan*/  u32 ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_device {int dummy; } ;
struct i40iw_ucontext {int abi_ver; } ;
struct i40iw_sc_pd {int dummy; } ;
struct i40iw_sc_dev {TYPE_1__* iw_pd_ops; } ;
struct i40iw_pd {struct ib_pd ibpd; struct i40iw_sc_pd sc_pd; } ;
struct i40iw_device {int /*<<< orphan*/  allocated_pds; int /*<<< orphan*/  next_pd; int /*<<< orphan*/  max_pd; scalar_t__ closing; struct i40iw_sc_dev sc_dev; } ;
struct i40iw_alloc_pd_resp {int /*<<< orphan*/  pd_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pd_init ) (struct i40iw_sc_dev*,struct i40iw_sc_pd*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct ib_pd* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i40iw_add_pdusecount (struct i40iw_pd*) ; 
 int i40iw_alloc_resource (struct i40iw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_resource (struct i40iw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_pr_err (char*) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct i40iw_alloc_pd_resp*,int) ; 
 int /*<<< orphan*/  kfree (struct i40iw_pd*) ; 
 struct i40iw_pd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct i40iw_alloc_pd_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct i40iw_sc_dev*,struct i40iw_sc_pd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct i40iw_sc_dev*,struct i40iw_sc_pd*,int /*<<< orphan*/ ,int) ; 
 struct i40iw_device* to_iwdev (struct ib_device*) ; 
 struct i40iw_ucontext* to_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static struct ib_pd *i40iw_alloc_pd(struct ib_device *ibdev,
				    struct ib_ucontext *context,
				    struct ib_udata *udata)
{
	struct i40iw_pd *iwpd;
	struct i40iw_device *iwdev = to_iwdev(ibdev);
	struct i40iw_sc_dev *dev = &iwdev->sc_dev;
	struct i40iw_alloc_pd_resp uresp;
	struct i40iw_sc_pd *sc_pd;
	struct i40iw_ucontext *ucontext;
	u32 pd_id = 0;
	int err;

	if (iwdev->closing)
		return ERR_PTR(-ENODEV);

	err = i40iw_alloc_resource(iwdev, iwdev->allocated_pds,
				   iwdev->max_pd, &pd_id, &iwdev->next_pd);
	if (err) {
		i40iw_pr_err("alloc resource failed\n");
		return ERR_PTR(err);
	}

	iwpd = kzalloc(sizeof(*iwpd), GFP_KERNEL);
	if (!iwpd) {
		err = -ENOMEM;
		goto free_res;
	}

	sc_pd = &iwpd->sc_pd;

	if (context) {
		ucontext = to_ucontext(context);
		dev->iw_pd_ops->pd_init(dev, sc_pd, pd_id, ucontext->abi_ver);
		memset(&uresp, 0, sizeof(uresp));
		uresp.pd_id = pd_id;
		if (ib_copy_to_udata(udata, &uresp, sizeof(uresp))) {
			err = -EFAULT;
			goto error;
		}
	} else {
		dev->iw_pd_ops->pd_init(dev, sc_pd, pd_id, -1);
	}

	i40iw_add_pdusecount(iwpd);
	return &iwpd->ibpd;
error:
	kfree(iwpd);
free_res:
	i40iw_free_resource(iwdev, iwdev->allocated_pds, pd_id);
	return ERR_PTR(err);
}