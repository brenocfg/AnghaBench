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
typedef  int /*<<< orphan*/  uresp ;
typedef  int /*<<< orphan*/  u32 ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_pd {int dummy; } ;
struct ib_device {int dummy; } ;
struct c4iw_pd {struct ib_pd ibpd; int /*<<< orphan*/  pdid; struct c4iw_dev* rhp; } ;
struct TYPE_6__ {scalar_t__ cur; scalar_t__ max; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__ pd; } ;
struct TYPE_5__ {int /*<<< orphan*/  pdid_table; } ;
struct TYPE_8__ {TYPE_3__ stats; TYPE_1__ resource; } ;
struct c4iw_dev {TYPE_4__ rdev; } ;
struct c4iw_alloc_pd_resp {int /*<<< orphan*/  pdid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_pd* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  c4iw_deallocate_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  c4iw_get_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c4iw_put_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct c4iw_alloc_pd_resp*,int) ; 
 struct c4iw_pd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static struct ib_pd *c4iw_allocate_pd(struct ib_device *ibdev,
				      struct ib_ucontext *context,
				      struct ib_udata *udata)
{
	struct c4iw_pd *php;
	u32 pdid;
	struct c4iw_dev *rhp;

	pr_debug("ibdev %p\n", ibdev);
	rhp = (struct c4iw_dev *) ibdev;
	pdid =  c4iw_get_resource(&rhp->rdev.resource.pdid_table);
	if (!pdid)
		return ERR_PTR(-EINVAL);
	php = kzalloc(sizeof(*php), GFP_KERNEL);
	if (!php) {
		c4iw_put_resource(&rhp->rdev.resource.pdid_table, pdid);
		return ERR_PTR(-ENOMEM);
	}
	php->pdid = pdid;
	php->rhp = rhp;
	if (context) {
		struct c4iw_alloc_pd_resp uresp = {.pdid = php->pdid};

		if (ib_copy_to_udata(udata, &uresp, sizeof(uresp))) {
			c4iw_deallocate_pd(&php->ibpd);
			return ERR_PTR(-EFAULT);
		}
	}
	mutex_lock(&rhp->rdev.stats.lock);
	rhp->rdev.stats.pd.cur++;
	if (rhp->rdev.stats.pd.cur > rhp->rdev.stats.pd.max)
		rhp->rdev.stats.pd.max = rhp->rdev.stats.pd.cur;
	mutex_unlock(&rhp->rdev.stats.lock);
	pr_debug("pdid 0x%0x ptr 0x%p\n", pdid, php);
	return &php->ibpd;
}