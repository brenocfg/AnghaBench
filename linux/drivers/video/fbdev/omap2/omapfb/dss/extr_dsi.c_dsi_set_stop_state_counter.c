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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DSI_TIMING1 ; 
 int /*<<< orphan*/  DSSDBG (char*,unsigned long,unsigned int,char*,char*,unsigned long) ; 
 int /*<<< orphan*/  FLD_MOD (int /*<<< orphan*/ ,unsigned int,int,int) ; 
 unsigned long dsi_fclk_rate (struct platform_device*) ; 
 int /*<<< orphan*/  dsi_read_reg (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write_reg (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_set_stop_state_counter(struct platform_device *dsidev,
		unsigned ticks, bool x4, bool x16)
{
	unsigned long fck;
	unsigned long total_ticks;
	u32 r;

	BUG_ON(ticks > 0x1fff);

	/* ticks in DSI_FCK */
	fck = dsi_fclk_rate(dsidev);

	r = dsi_read_reg(dsidev, DSI_TIMING1);
	r = FLD_MOD(r, 1, 15, 15);	/* FORCE_TX_STOP_MODE_IO */
	r = FLD_MOD(r, x16 ? 1 : 0, 14, 14);	/* STOP_STATE_X16_IO */
	r = FLD_MOD(r, x4 ? 1 : 0, 13, 13);	/* STOP_STATE_X4_IO */
	r = FLD_MOD(r, ticks, 12, 0);	/* STOP_STATE_COUNTER_IO */
	dsi_write_reg(dsidev, DSI_TIMING1, r);

	total_ticks = ticks * (x16 ? 16 : 1) * (x4 ? 4 : 1);

	DSSDBG("STOP_STATE_COUNTER %lu ticks (%#x%s%s) = %lu ns\n",
			total_ticks,
			ticks, x4 ? " x4" : "", x16 ? " x16" : "",
			(total_ticks * 1000) / (fck / 1000 / 1000));
}