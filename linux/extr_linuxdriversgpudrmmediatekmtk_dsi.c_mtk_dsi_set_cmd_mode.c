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
struct mtk_dsi {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MODE ; 
 scalar_t__ DSI_MODE_CTRL ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mtk_dsi_set_cmd_mode(struct mtk_dsi *dsi)
{
	writel(CMD_MODE, dsi->regs + DSI_MODE_CTRL);
}