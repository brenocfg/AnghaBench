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
struct mthca_mr {struct ib_mr ibmr; int /*<<< orphan*/ * umem; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  pd_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_mr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  convert_access (int) ; 
 int /*<<< orphan*/  kfree (struct mthca_mr*) ; 
 struct mthca_mr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mthca_mr_alloc_notrans (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mthca_mr*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static struct ib_mr *mthca_get_dma_mr(struct ib_pd *pd, int acc)
{
	struct mthca_mr *mr;
	int err;

	mr = kmalloc(sizeof *mr, GFP_KERNEL);
	if (!mr)
		return ERR_PTR(-ENOMEM);

	err = mthca_mr_alloc_notrans(to_mdev(pd->device),
				     to_mpd(pd)->pd_num,
				     convert_access(acc), mr);

	if (err) {
		kfree(mr);
		return ERR_PTR(err);
	}

	mr->umem = NULL;

	return &mr->ibmr;
}