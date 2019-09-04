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
struct ib_fmr {int dummy; } ;
struct mthca_fmr {struct ib_fmr ibmr; int /*<<< orphan*/  attr; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_fmr_attr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pd_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_fmr* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  convert_access (int) ; 
 int /*<<< orphan*/  kfree (struct mthca_fmr*) ; 
 struct mthca_fmr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ib_fmr_attr*,int) ; 
 int mthca_fmr_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mthca_fmr*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static struct ib_fmr *mthca_alloc_fmr(struct ib_pd *pd, int mr_access_flags,
				      struct ib_fmr_attr *fmr_attr)
{
	struct mthca_fmr *fmr;
	int err;

	fmr = kmalloc(sizeof *fmr, GFP_KERNEL);
	if (!fmr)
		return ERR_PTR(-ENOMEM);

	memcpy(&fmr->attr, fmr_attr, sizeof *fmr_attr);
	err = mthca_fmr_alloc(to_mdev(pd->device), to_mpd(pd)->pd_num,
			     convert_access(mr_access_flags), fmr);

	if (err) {
		kfree(fmr);
		return ERR_PTR(err);
	}

	return &fmr->ibmr;
}