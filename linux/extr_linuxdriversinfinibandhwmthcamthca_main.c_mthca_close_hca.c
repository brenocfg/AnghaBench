#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fw_icm; } ;
struct TYPE_4__ {TYPE_1__ arbel; } ;
struct mthca_dev {int mthca_flags; TYPE_2__ fw; } ;

/* Variables and functions */
 int MTHCA_FLAG_NO_LAM ; 
 int /*<<< orphan*/  mthca_CLOSE_HCA (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_DISABLE_LAM (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_SYS_DIS (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_UNMAP_FA (struct mthca_dev*) ; 
 int /*<<< orphan*/  mthca_free_icm (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_free_icms (struct mthca_dev*) ; 
 scalar_t__ mthca_is_memfree (struct mthca_dev*) ; 

__attribute__((used)) static void mthca_close_hca(struct mthca_dev *mdev)
{
	mthca_CLOSE_HCA(mdev, 0);

	if (mthca_is_memfree(mdev)) {
		mthca_free_icms(mdev);

		mthca_UNMAP_FA(mdev);
		mthca_free_icm(mdev, mdev->fw.arbel.fw_icm, 0);

		if (!(mdev->mthca_flags & MTHCA_FLAG_NO_LAM))
			mthca_DISABLE_LAM(mdev);
	} else
		mthca_SYS_DIS(mdev);
}