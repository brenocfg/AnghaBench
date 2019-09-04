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
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_sc_dev {int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;
typedef  enum i40iw_status_code { ____Placeholder_i40iw_status_code } i40iw_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFPE_AEQALLOC ; 
 int /*<<< orphan*/  I40E_VFPE_AEQALLOC1 ; 
 int /*<<< orphan*/  i40iw_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum i40iw_status_code i40iw_sc_repost_aeq_entries(struct i40iw_sc_dev *dev,
							  u32 count)
{

	if (dev->is_pf)
		i40iw_wr32(dev->hw, I40E_PFPE_AEQALLOC, count);
	else
		i40iw_wr32(dev->hw, I40E_VFPE_AEQALLOC1, count);

	return 0;
}