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
struct dfl_fme {int /*<<< orphan*/  mgr; } ;
struct dfl_feature_platform_data {int dummy; } ;

/* Variables and functions */
 struct dfl_fme* dfl_fpga_pdata_get_private (struct dfl_feature_platform_data*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfl_fme_destroy_mgr(struct dfl_feature_platform_data *pdata)
{
	struct dfl_fme *priv = dfl_fpga_pdata_get_private(pdata);

	platform_device_unregister(priv->mgr);
}