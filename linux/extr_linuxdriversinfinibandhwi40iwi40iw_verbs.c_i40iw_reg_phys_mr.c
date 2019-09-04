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
typedef  void* u64 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_mr {void* lkey; void* rkey; int /*<<< orphan*/  device; struct ib_pd* pd; } ;
struct i40iw_pd {int dummy; } ;
struct i40iw_pbl {void* user_base; struct i40iw_mr* iwmr; } ;
struct i40iw_mr {int page_cnt; struct ib_mr ibmr; void* length; void** pgaddrmem; void* stag; int /*<<< orphan*/  type; struct i40iw_pbl iwpbl; } ;
struct i40iw_device {int dummy; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int ENOMEM ; 
 int EOVERFLOW ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40IW_ACCESS_FLAGS_LOCALREAD ; 
 int /*<<< orphan*/  IW_MEMREG_TYPE_MEM ; 
 int /*<<< orphan*/  i40iw_add_pdusecount (struct i40iw_pd*) ; 
 void* i40iw_create_stag (struct i40iw_device*) ; 
 int /*<<< orphan*/  i40iw_free_stag (struct i40iw_device*,void*) ; 
 int /*<<< orphan*/  i40iw_get_user_access (int) ; 
 int i40iw_hwreg_mr (struct i40iw_device*,struct i40iw_mr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i40iw_mr*) ; 
 struct i40iw_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 
 struct i40iw_pd* to_iwpd (struct ib_pd*) ; 

struct ib_mr *i40iw_reg_phys_mr(struct ib_pd *pd,
				u64 addr,
				u64 size,
				int acc,
				u64 *iova_start)
{
	struct i40iw_pd *iwpd = to_iwpd(pd);
	struct i40iw_device *iwdev = to_iwdev(pd->device);
	struct i40iw_pbl *iwpbl;
	struct i40iw_mr *iwmr;
	enum i40iw_status_code status;
	u32 stag;
	u16 access = I40IW_ACCESS_FLAGS_LOCALREAD;
	int ret;

	iwmr = kzalloc(sizeof(*iwmr), GFP_KERNEL);
	if (!iwmr)
		return ERR_PTR(-ENOMEM);
	iwmr->ibmr.pd = pd;
	iwmr->ibmr.device = pd->device;
	iwpbl = &iwmr->iwpbl;
	iwpbl->iwmr = iwmr;
	iwmr->type = IW_MEMREG_TYPE_MEM;
	iwpbl->user_base = *iova_start;
	stag = i40iw_create_stag(iwdev);
	if (!stag) {
		ret = -EOVERFLOW;
		goto err;
	}
	access |= i40iw_get_user_access(acc);
	iwmr->stag = stag;
	iwmr->ibmr.rkey = stag;
	iwmr->ibmr.lkey = stag;
	iwmr->page_cnt = 1;
	iwmr->pgaddrmem[0]  = addr;
	iwmr->length = size;
	status = i40iw_hwreg_mr(iwdev, iwmr, access);
	if (status) {
		i40iw_free_stag(iwdev, stag);
		ret = -ENOMEM;
		goto err;
	}

	i40iw_add_pdusecount(iwpd);
	return &iwmr->ibmr;
 err:
	kfree(iwmr);
	return ERR_PTR(ret);
}