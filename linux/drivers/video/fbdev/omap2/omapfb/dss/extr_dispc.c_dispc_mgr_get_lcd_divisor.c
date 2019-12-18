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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_DIVISORo (int) ; 
 int FLD_GET (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_mgr_get_lcd_divisor(enum omap_channel channel, int *lck_div,
		int *pck_div)
{
	u32 l;
	l = dispc_read_reg(DISPC_DIVISORo(channel));
	*lck_div = FLD_GET(l, 23, 16);
	*pck_div = FLD_GET(l, 7, 0);
}