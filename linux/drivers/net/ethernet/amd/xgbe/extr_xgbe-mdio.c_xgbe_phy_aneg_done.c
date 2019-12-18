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
struct xgbe_prv_data {scalar_t__ an_result; } ;

/* Variables and functions */
 scalar_t__ XGBE_AN_COMPLETE ; 

__attribute__((used)) static bool xgbe_phy_aneg_done(struct xgbe_prv_data *pdata)
{
	return (pdata->an_result == XGBE_AN_COMPLETE);
}