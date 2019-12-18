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
typedef  int u32 ;
struct mtk_dsi {int data_rate; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DSI_PHY_TIMECON0 ; 
 scalar_t__ DSI_PHY_TIMECON1 ; 
 scalar_t__ DSI_PHY_TIMECON2 ; 
 scalar_t__ DSI_PHY_TIMECON3 ; 
 int NS_TO_CYCLE (int,int) ; 
 int T_HS_EXIT ; 
 int T_HS_PREP ; 
 int T_HS_TRAIL ; 
 int T_HS_ZERO ; 
 int T_LPX ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtk_dsi_phy_timconfig(struct mtk_dsi *dsi)
{
	u32 timcon0, timcon1, timcon2, timcon3;
	u32 ui, cycle_time;

	ui = 1000 / dsi->data_rate + 0x01;
	cycle_time = 8000 / dsi->data_rate + 0x01;

	timcon0 = T_LPX | T_HS_PREP << 8 | T_HS_ZERO << 16 | T_HS_TRAIL << 24;
	timcon1 = 4 * T_LPX | (3 * T_LPX / 2) << 8 | 5 * T_LPX << 16 |
		  T_HS_EXIT << 24;
	timcon2 = ((NS_TO_CYCLE(0x64, cycle_time) + 0xa) << 24) |
		  (NS_TO_CYCLE(0x150, cycle_time) << 16);
	timcon3 = NS_TO_CYCLE(0x40, cycle_time) | (2 * T_LPX) << 16 |
		  NS_TO_CYCLE(80 + 52 * ui, cycle_time) << 8;

	writel(timcon0, dsi->regs + DSI_PHY_TIMECON0);
	writel(timcon1, dsi->regs + DSI_PHY_TIMECON1);
	writel(timcon2, dsi->regs + DSI_PHY_TIMECON2);
	writel(timcon3, dsi->regs + DSI_PHY_TIMECON3);
}