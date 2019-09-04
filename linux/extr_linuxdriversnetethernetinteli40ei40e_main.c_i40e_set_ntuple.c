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
struct i40e_pf {int flags; scalar_t__ num_fdsb_msix; TYPE_2__* pdev; TYPE_1__ hw; int /*<<< orphan*/  state; scalar_t__ fd_atr_cnt; scalar_t__ fd_add_err; int /*<<< orphan*/  num_cloud_filters; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I40E_DEBUG_FD ; 
 int I40E_FLAG_FD_ATR_ENABLED ; 
 int I40E_FLAG_FD_SB_ENABLED ; 
 int I40E_FLAG_FD_SB_INACTIVE ; 
 int NETIF_F_NTUPLE ; 
 int /*<<< orphan*/  __I40E_FD_ATR_AUTO_DISABLED ; 
 int /*<<< orphan*/  __I40E_FD_SB_AUTO_DISABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_fdir_filter_exit (struct i40e_pf*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool i40e_set_ntuple(struct i40e_pf *pf, netdev_features_t features)
{
	bool need_reset = false;

	/* Check if Flow Director n-tuple support was enabled or disabled.  If
	 * the state changed, we need to reset.
	 */
	if (features & NETIF_F_NTUPLE) {
		/* Enable filters and mark for reset */
		if (!(pf->flags & I40E_FLAG_FD_SB_ENABLED))
			need_reset = true;
		/* enable FD_SB only if there is MSI-X vector and no cloud
		 * filters exist
		 */
		if (pf->num_fdsb_msix > 0 && !pf->num_cloud_filters) {
			pf->flags |= I40E_FLAG_FD_SB_ENABLED;
			pf->flags &= ~I40E_FLAG_FD_SB_INACTIVE;
		}
	} else {
		/* turn off filters, mark for reset and clear SW filter list */
		if (pf->flags & I40E_FLAG_FD_SB_ENABLED) {
			need_reset = true;
			i40e_fdir_filter_exit(pf);
		}
		pf->flags &= ~I40E_FLAG_FD_SB_ENABLED;
		clear_bit(__I40E_FD_SB_AUTO_DISABLED, pf->state);
		pf->flags |= I40E_FLAG_FD_SB_INACTIVE;

		/* reset fd counters */
		pf->fd_add_err = 0;
		pf->fd_atr_cnt = 0;
		/* if ATR was auto disabled it can be re-enabled. */
		if (test_and_clear_bit(__I40E_FD_ATR_AUTO_DISABLED, pf->state))
			if ((pf->flags & I40E_FLAG_FD_ATR_ENABLED) &&
			    (I40E_DEBUG_FD & pf->hw.debug_mask))
				dev_info(&pf->pdev->dev, "ATR re-enabled.\n");
	}
	return need_reset;
}