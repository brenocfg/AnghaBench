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
struct ib_mr {int dummy; } ;
struct siw_mr {struct ib_mr base_mr; TYPE_1__* mem; } ;
struct siw_device {int /*<<< orphan*/  num_mr; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int stag_valid; int /*<<< orphan*/  stag; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SIW_MAX_MR ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct siw_mr*) ; 
 struct siw_mr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siw_dbg_pd (struct ib_pd*,char*,...) ; 
 int siw_mr_add_mem (struct siw_mr*,struct ib_pd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct siw_device* to_siw_dev (int /*<<< orphan*/ ) ; 

struct ib_mr *siw_get_dma_mr(struct ib_pd *pd, int rights)
{
	struct siw_device *sdev = to_siw_dev(pd->device);
	struct siw_mr *mr = NULL;
	int rv;

	if (atomic_inc_return(&sdev->num_mr) > SIW_MAX_MR) {
		siw_dbg_pd(pd, "too many mr's\n");
		rv = -ENOMEM;
		goto err_out;
	}
	mr = kzalloc(sizeof(*mr), GFP_KERNEL);
	if (!mr) {
		rv = -ENOMEM;
		goto err_out;
	}
	rv = siw_mr_add_mem(mr, pd, NULL, 0, ULONG_MAX, rights);
	if (rv)
		goto err_out;

	mr->mem->stag_valid = 1;

	siw_dbg_pd(pd, "[MEM %u]: success\n", mr->mem->stag);

	return &mr->base_mr;

err_out:
	if (rv)
		kfree(mr);

	atomic_dec(&sdev->num_mr);

	return ERR_PTR(rv);
}