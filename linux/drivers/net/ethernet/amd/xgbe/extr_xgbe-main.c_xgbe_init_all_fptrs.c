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
struct xgbe_prv_data {int /*<<< orphan*/  phy_if; TYPE_1__* vdata; int /*<<< orphan*/  desc_if; int /*<<< orphan*/  i2c_if; int /*<<< orphan*/  hw_if; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init_function_ptrs_phy_impl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_init_function_ptrs_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_init_function_ptrs_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_init_function_ptrs_i2c (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgbe_init_function_ptrs_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgbe_init_all_fptrs(struct xgbe_prv_data *pdata)
{
	xgbe_init_function_ptrs_dev(&pdata->hw_if);
	xgbe_init_function_ptrs_phy(&pdata->phy_if);
	xgbe_init_function_ptrs_i2c(&pdata->i2c_if);
	xgbe_init_function_ptrs_desc(&pdata->desc_if);

	pdata->vdata->init_function_ptrs_phy_impl(&pdata->phy_if);
}