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
struct xgbe_prv_data {scalar_t__ debugfs_an_cdr_track_early; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgbe_phy_cdr_track (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_kr_training_pre(struct xgbe_prv_data *pdata)
{
	if (pdata->debugfs_an_cdr_track_early)
		xgbe_phy_cdr_track(pdata);
}