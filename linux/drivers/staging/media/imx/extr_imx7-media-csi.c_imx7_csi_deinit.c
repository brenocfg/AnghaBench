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
struct imx7_csi {int is_init; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx7_csi_dmareq_rff_disable (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_hw_reset (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_init_interface (struct imx7_csi*) ; 

__attribute__((used)) static void imx7_csi_deinit(struct imx7_csi *csi)
{
	if (!csi->is_init)
		return;

	imx7_csi_hw_reset(csi);
	imx7_csi_init_interface(csi);
	imx7_csi_dmareq_rff_disable(csi);
	clk_disable_unprepare(csi->mclk);

	csi->is_init = false;
}