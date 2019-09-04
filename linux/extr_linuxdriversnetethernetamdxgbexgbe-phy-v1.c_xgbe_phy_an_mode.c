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
struct xgbe_prv_data {int dummy; } ;
typedef  enum xgbe_an_mode { ____Placeholder_xgbe_an_mode } xgbe_an_mode ;

/* Variables and functions */
 int XGBE_AN_MODE_CL73 ; 

__attribute__((used)) static enum xgbe_an_mode xgbe_phy_an_mode(struct xgbe_prv_data *pdata)
{
	return XGBE_AN_MODE_CL73;
}