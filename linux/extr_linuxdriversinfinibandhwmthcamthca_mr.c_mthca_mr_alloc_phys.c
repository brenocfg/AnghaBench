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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mthca_mr {int /*<<< orphan*/  mtt; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_alloc_mtt (struct mthca_dev*,int) ; 
 int /*<<< orphan*/  mthca_free_mtt (struct mthca_dev*,int /*<<< orphan*/ ) ; 
 int mthca_mr_alloc (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mthca_mr*) ; 
 int mthca_write_mtt (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int mthca_mr_alloc_phys(struct mthca_dev *dev, u32 pd,
			u64 *buffer_list, int buffer_size_shift,
			int list_len, u64 iova, u64 total_size,
			u32 access, struct mthca_mr *mr)
{
	int err;

	mr->mtt = mthca_alloc_mtt(dev, list_len);
	if (IS_ERR(mr->mtt))
		return PTR_ERR(mr->mtt);

	err = mthca_write_mtt(dev, mr->mtt, 0, buffer_list, list_len);
	if (err) {
		mthca_free_mtt(dev, mr->mtt);
		return err;
	}

	err = mthca_mr_alloc(dev, pd, buffer_size_shift, iova,
			     total_size, access, mr);
	if (err)
		mthca_free_mtt(dev, mr->mtt);

	return err;
}