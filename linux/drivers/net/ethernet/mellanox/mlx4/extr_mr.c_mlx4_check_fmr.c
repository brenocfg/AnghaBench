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
typedef  int u64 ;
struct mlx4_fmr {int max_pages; int page_shift; scalar_t__ maps; scalar_t__ max_maps; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int mlx4_check_fmr(struct mlx4_fmr *fmr, u64 *page_list,
				  int npages, u64 iova)
{
	int i, page_mask;

	if (npages > fmr->max_pages)
		return -EINVAL;

	page_mask = (1 << fmr->page_shift) - 1;

	/* We are getting page lists, so va must be page aligned. */
	if (iova & page_mask)
		return -EINVAL;

	/* Trust the user not to pass misaligned data in page_list */
	if (0)
		for (i = 0; i < npages; ++i) {
			if (page_list[i] & ~page_mask)
				return -EINVAL;
		}

	if (fmr->maps >= fmr->max_maps)
		return -EINVAL;

	return 0;
}