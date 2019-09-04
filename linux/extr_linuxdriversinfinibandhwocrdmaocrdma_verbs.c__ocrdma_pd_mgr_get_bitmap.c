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
typedef  int /*<<< orphan*/  u16 ;
struct ocrdma_dev {TYPE_1__* pd_mgr; } ;
struct TYPE_2__ {unsigned long* pd_dpp_bitmap; scalar_t__ pd_dpp_count; scalar_t__ pd_dpp_thrsh; unsigned long* pd_norm_bitmap; scalar_t__ pd_norm_count; scalar_t__ pd_norm_thrsh; int /*<<< orphan*/  max_normal_pd; int /*<<< orphan*/  max_dpp_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  find_first_zero_bit (unsigned long const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 _ocrdma_pd_mgr_get_bitmap(struct ocrdma_dev *dev, bool dpp_pool)
{
	u16 pd_bitmap_idx = 0;
	const unsigned long *pd_bitmap;

	if (dpp_pool) {
		pd_bitmap = dev->pd_mgr->pd_dpp_bitmap;
		pd_bitmap_idx = find_first_zero_bit(pd_bitmap,
						    dev->pd_mgr->max_dpp_pd);
		__set_bit(pd_bitmap_idx, dev->pd_mgr->pd_dpp_bitmap);
		dev->pd_mgr->pd_dpp_count++;
		if (dev->pd_mgr->pd_dpp_count > dev->pd_mgr->pd_dpp_thrsh)
			dev->pd_mgr->pd_dpp_thrsh = dev->pd_mgr->pd_dpp_count;
	} else {
		pd_bitmap = dev->pd_mgr->pd_norm_bitmap;
		pd_bitmap_idx = find_first_zero_bit(pd_bitmap,
						    dev->pd_mgr->max_normal_pd);
		__set_bit(pd_bitmap_idx, dev->pd_mgr->pd_norm_bitmap);
		dev->pd_mgr->pd_norm_count++;
		if (dev->pd_mgr->pd_norm_count > dev->pd_mgr->pd_norm_thrsh)
			dev->pd_mgr->pd_norm_thrsh = dev->pd_mgr->pd_norm_count;
	}
	return pd_bitmap_idx;
}