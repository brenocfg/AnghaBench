#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uresp ;
struct mthca_ucontext {scalar_t__ reg_mr_warned; int /*<<< orphan*/  uar; int /*<<< orphan*/  db_tab; } ;
struct mthca_alloc_ucontext_resp {scalar_t__ uarc_size; int /*<<< orphan*/  qp_tab_size; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {struct ib_device* device; } ;
struct ib_device {int dummy; } ;
struct TYPE_10__ {scalar_t__ uarc_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  num_qps; } ;
struct TYPE_11__ {TYPE_2__ uar_table; TYPE_1__ limits; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_copy_to_udata (struct ib_udata*,struct mthca_alloc_ucontext_resp*,int) ; 
 int /*<<< orphan*/  mthca_cleanup_user_db_tab (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_init_user_db_tab (TYPE_3__*) ; 
 scalar_t__ mthca_is_memfree (TYPE_3__*) ; 
 int mthca_uar_alloc (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_uar_free (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* to_mdev (struct ib_device*) ; 
 struct mthca_ucontext* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int mthca_alloc_ucontext(struct ib_ucontext *uctx,
				struct ib_udata *udata)
{
	struct ib_device *ibdev = uctx->device;
	struct mthca_alloc_ucontext_resp uresp = {};
	struct mthca_ucontext *context = to_mucontext(uctx);
	int                              err;

	if (!(to_mdev(ibdev)->active))
		return -EAGAIN;

	uresp.qp_tab_size = to_mdev(ibdev)->limits.num_qps;
	if (mthca_is_memfree(to_mdev(ibdev)))
		uresp.uarc_size = to_mdev(ibdev)->uar_table.uarc_size;
	else
		uresp.uarc_size = 0;

	err = mthca_uar_alloc(to_mdev(ibdev), &context->uar);
	if (err)
		return err;

	context->db_tab = mthca_init_user_db_tab(to_mdev(ibdev));
	if (IS_ERR(context->db_tab)) {
		err = PTR_ERR(context->db_tab);
		mthca_uar_free(to_mdev(ibdev), &context->uar);
		return err;
	}

	if (ib_copy_to_udata(udata, &uresp, sizeof(uresp))) {
		mthca_cleanup_user_db_tab(to_mdev(ibdev), &context->uar, context->db_tab);
		mthca_uar_free(to_mdev(ibdev), &context->uar);
		return -EFAULT;
	}

	context->reg_mr_warned = 0;

	return 0;
}