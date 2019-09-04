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
struct analogix_dp_plat_data {int dummy; } ;

/* Variables and functions */
 int exynos_dp_crtc_clock_enable (struct analogix_dp_plat_data*,int) ; 

__attribute__((used)) static int exynos_dp_poweroff(struct analogix_dp_plat_data *plat_data)
{
	return exynos_dp_crtc_clock_enable(plat_data, false);
}