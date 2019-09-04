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
struct cal_ctx {int /*<<< orphan*/  csi2_port; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAL_CSI2_PPI_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAL_CSI2_PPI_CTRL_IF_EN_MASK ; 
 int /*<<< orphan*/  CAL_GEN_ENABLE ; 
 int /*<<< orphan*/  reg_write_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csi2_ppi_enable(struct cal_ctx *ctx)
{
	reg_write_field(ctx->dev, CAL_CSI2_PPI_CTRL(ctx->csi2_port),
			CAL_GEN_ENABLE, CAL_CSI2_PPI_CTRL_IF_EN_MASK);
}