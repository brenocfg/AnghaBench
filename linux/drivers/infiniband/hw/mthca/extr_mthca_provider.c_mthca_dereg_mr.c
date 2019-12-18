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
struct mthca_mr {int /*<<< orphan*/  umem; } ;
struct ib_udata {int dummy; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mthca_mr*) ; 
 int /*<<< orphan*/  mthca_free_mr (int /*<<< orphan*/ ,struct mthca_mr*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 struct mthca_mr* to_mmr (struct ib_mr*) ; 

__attribute__((used)) static int mthca_dereg_mr(struct ib_mr *mr, struct ib_udata *udata)
{
	struct mthca_mr *mmr = to_mmr(mr);

	mthca_free_mr(to_mdev(mr->device), mmr);
	ib_umem_release(mmr->umem);
	kfree(mmr);

	return 0;
}