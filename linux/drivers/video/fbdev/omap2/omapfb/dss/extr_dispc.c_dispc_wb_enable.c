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

/* Variables and functions */
 int /*<<< orphan*/  OMAP_DSS_WB ; 
 int /*<<< orphan*/  dispc_ovl_enable (int /*<<< orphan*/ ,int) ; 

void dispc_wb_enable(bool enable)
{
	dispc_ovl_enable(OMAP_DSS_WB, enable);
}