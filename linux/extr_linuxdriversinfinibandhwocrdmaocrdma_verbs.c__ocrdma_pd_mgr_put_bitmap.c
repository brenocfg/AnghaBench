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
typedef  scalar_t__ u16 ;
struct ocrdma_dev {TYPE_1__* pd_mgr; } ;
struct TYPE_2__ {scalar_t__ pd_dpp_count; scalar_t__ pd_norm_count; scalar_t__ pd_dpp_start; scalar_t__ max_dpp_pd; scalar_t__ pd_norm_start; scalar_t__ max_normal_pd; int /*<<< orphan*/  pd_norm_bitmap; int /*<<< orphan*/  pd_dpp_bitmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ocrdma_pd_mgr_put_bitmap(struct ocrdma_dev *dev, u16 pd_id,
					bool dpp_pool)
{
	u16 pd_count;
	u16 pd_bit_index;

	pd_count = dpp_pool ? dev->pd_mgr->pd_dpp_count :
			      dev->pd_mgr->pd_norm_count;
	if (pd_count == 0)
		return -EINVAL;

	if (dpp_pool) {
		pd_bit_index = pd_id - dev->pd_mgr->pd_dpp_start;
		if (pd_bit_index >= dev->pd_mgr->max_dpp_pd) {
			return -EINVAL;
		} else {
			__clear_bit(pd_bit_index, dev->pd_mgr->pd_dpp_bitmap);
			dev->pd_mgr->pd_dpp_count--;
		}
	} else {
		pd_bit_index = pd_id - dev->pd_mgr->pd_norm_start;
		if (pd_bit_index >= dev->pd_mgr->max_normal_pd) {
			return -EINVAL;
		} else {
			__clear_bit(pd_bit_index, dev->pd_mgr->pd_norm_bitmap);
			dev->pd_mgr->pd_norm_count--;
		}
	}

	return 0;
}