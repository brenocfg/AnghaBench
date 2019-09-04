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
struct mtk_dsi {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int DSI_BUSY ; 
 scalar_t__ DSI_INTSTA ; 
 int /*<<< orphan*/  mtk_dsi_enable (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_reset_engine (struct mtk_dsi*) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static void mtk_dsi_wait_for_idle(struct mtk_dsi *dsi)
{
	int ret;
	u32 val;

	ret = readl_poll_timeout(dsi->regs + DSI_INTSTA, val, !(val & DSI_BUSY),
				 4, 2000000);
	if (ret) {
		DRM_WARN("polling dsi wait not busy timeout!\n");

		mtk_dsi_enable(dsi);
		mtk_dsi_reset_engine(dsi);
	}
}