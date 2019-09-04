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
struct mthca_fmr {int dummy; } ;
struct ib_fmr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mthca_fmr*) ; 
 int mthca_free_fmr (int /*<<< orphan*/ ,struct mthca_fmr*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 struct mthca_fmr* to_mfmr (struct ib_fmr*) ; 

__attribute__((used)) static int mthca_dealloc_fmr(struct ib_fmr *fmr)
{
	struct mthca_fmr *mfmr = to_mfmr(fmr);
	int err;

	err = mthca_free_fmr(to_mdev(fmr->device), mfmr);
	if (err)
		return err;

	kfree(mfmr);
	return 0;
}