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
struct meson_mx_efuse {int /*<<< orphan*/  core_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL1 ; 
 int /*<<< orphan*/  MESON_MX_EFUSE_CNTL1_PD_ENABLE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_mx_efuse_mask_bits (struct meson_mx_efuse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_mx_efuse_hw_disable(struct meson_mx_efuse *efuse)
{
	meson_mx_efuse_mask_bits(efuse, MESON_MX_EFUSE_CNTL1,
				 MESON_MX_EFUSE_CNTL1_PD_ENABLE,
				 MESON_MX_EFUSE_CNTL1_PD_ENABLE);

	clk_disable_unprepare(efuse->core_clk);
}