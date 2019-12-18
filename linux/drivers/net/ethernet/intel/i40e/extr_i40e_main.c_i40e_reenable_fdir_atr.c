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
struct TYPE_3__ {int debug_mask; } ;
struct i40e_pf {int flags; TYPE_2__* pdev; TYPE_1__ hw; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I40E_DEBUG_FD ; 
 int /*<<< orphan*/  I40E_FILTER_PCTYPE_NONF_IPV4_TCP ; 
 int I40E_FLAG_FD_ATR_ENABLED ; 
 int I40E_L3_DST_MASK ; 
 int I40E_L3_SRC_MASK ; 
 int I40E_L4_DST_MASK ; 
 int I40E_L4_SRC_MASK ; 
 int /*<<< orphan*/  __I40E_FD_ATR_AUTO_DISABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_write_fd_input_set (struct i40e_pf*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_reenable_fdir_atr(struct i40e_pf *pf)
{
	if (test_and_clear_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state)) {
		/* ATR uses the same filtering logic as SB rules. It only
		 * functions properly if the input set mask is at the default
		 * settings. It is safe to restore the default input set
		 * because there are no active TCPv4 filter rules.
		 */
		i40e_write_fd_input_set(pf, I40E_FILTER_PCTYPE_NONF_IPV4_TCP,
					I40E_L3_SRC_MASK | I40E_L3_DST_MASK |
					I40E_L4_SRC_MASK | I40E_L4_DST_MASK);

		if ((pf->flags & I40E_FLAG_FD_ATR_ENABLED) &&
		    (I40E_DEBUG_FD & pf->hw.debug_mask))
			dev_info(&pf->pdev->dev, "ATR is being enabled since we have space in the table and there are no conflicting ntuple rules\n");
	}
}