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
struct rockchip_dp_device {int /*<<< orphan*/  pclk; } ;
struct analogix_dp_plat_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct rockchip_dp_device* to_dp (struct analogix_dp_plat_data*) ; 

__attribute__((used)) static int rockchip_dp_powerdown(struct analogix_dp_plat_data *plat_data)
{
	struct rockchip_dp_device *dp = to_dp(plat_data);

	clk_disable_unprepare(dp->pclk);

	return 0;
}