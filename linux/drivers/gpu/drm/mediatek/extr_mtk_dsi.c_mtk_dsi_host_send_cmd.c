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
typedef  int /*<<< orphan*/  u8 ;
struct mtk_dsi {int dummy; } ;
struct mipi_dsi_msg {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  mtk_dsi_cmdq (struct mtk_dsi*,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  mtk_dsi_irq_data_clear (struct mtk_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_dsi_start (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_wait_for_idle (struct mtk_dsi*) ; 
 int /*<<< orphan*/  mtk_dsi_wait_for_irq_done (struct mtk_dsi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t mtk_dsi_host_send_cmd(struct mtk_dsi *dsi,
				     const struct mipi_dsi_msg *msg, u8 flag)
{
	mtk_dsi_wait_for_idle(dsi);
	mtk_dsi_irq_data_clear(dsi, flag);
	mtk_dsi_cmdq(dsi, msg);
	mtk_dsi_start(dsi);

	if (!mtk_dsi_wait_for_irq_done(dsi, flag, 2000))
		return -ETIME;
	else
		return 0;
}