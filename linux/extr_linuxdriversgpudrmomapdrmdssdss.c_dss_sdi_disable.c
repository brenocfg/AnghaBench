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
struct dss_device {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSS_PLL_CONTROL ; 
 int /*<<< orphan*/  REG_FLD_MOD (struct dss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dispc_lcd_enable_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_pck_free_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dss_sdi_disable(struct dss_device *dss)
{
	dispc_lcd_enable_signal(dss->dispc, 0);

	dispc_pck_free_enable(dss->dispc, 0);

	/* Reset SDI PLL */
	REG_FLD_MOD(dss, DSS_PLL_CONTROL, 0, 18, 18); /* SDI_PLL_SYSRESET */
}