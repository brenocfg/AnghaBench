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
struct timer_list {int dummy; } ;
struct dev_info {int /*<<< orphan*/  mib_timer_info; scalar_t__ pme_wait; int /*<<< orphan*/  hw; int /*<<< orphan*/  mib_read; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int HZ ; 
 struct dev_info* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ hw_chk_wol_pme_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_clr_wol_pme_status (int /*<<< orphan*/ *) ; 
 struct dev_info* hw_priv ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ksz_update_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mib_read_work (int /*<<< orphan*/ *) ; 
 TYPE_1__ mib_timer_info ; 
 scalar_t__ time_is_before_eq_jiffies (scalar_t__) ; 

__attribute__((used)) static void mib_monitor(struct timer_list *t)
{
	struct dev_info *hw_priv = from_timer(hw_priv, t, mib_timer_info.timer);

	mib_read_work(&hw_priv->mib_read);

	/* This is used to verify Wake-on-LAN is working. */
	if (hw_priv->pme_wait) {
		if (time_is_before_eq_jiffies(hw_priv->pme_wait)) {
			hw_clr_wol_pme_status(&hw_priv->hw);
			hw_priv->pme_wait = 0;
		}
	} else if (hw_chk_wol_pme_status(&hw_priv->hw)) {

		/* PME is asserted.  Wait 2 seconds to clear it. */
		hw_priv->pme_wait = jiffies + HZ * 2;
	}

	ksz_update_timer(&hw_priv->mib_timer_info);
}