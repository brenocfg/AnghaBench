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
struct dcbnl_rtnl_ops {int dummy; } ;

/* Variables and functions */
 struct dcbnl_rtnl_ops const xgbe_dcbnl_ops ; 

const struct dcbnl_rtnl_ops *xgbe_get_dcbnl_ops(void)
{
	return &xgbe_dcbnl_ops;
}