#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct cal_ctx {int csi2_port; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {TYPE_2__* cm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CAMERRX_CTRL_CSI0_CTRLCLKEN_MASK ; 
 int /*<<< orphan*/  CM_CAMERRX_CTRL_CSI1_CTRLCLKEN_MASK ; 
 int /*<<< orphan*/  CM_CTRL_CORE_CAMERRX_CONTROL ; 
 int /*<<< orphan*/  ctx_err (struct cal_ctx*,char*) ; 
 int /*<<< orphan*/  reg_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void camerarx_phy_disable(struct cal_ctx *ctx)
{
	u32 val;

	if (!ctx->dev->cm->base) {
		ctx_err(ctx, "cm not mapped\n");
		return;
	}

	val = reg_read(ctx->dev->cm, CM_CTRL_CORE_CAMERRX_CONTROL);
	if (ctx->csi2_port == 1)
		set_field(&val, 0x0, CM_CAMERRX_CTRL_CSI0_CTRLCLKEN_MASK);
	else if (ctx->csi2_port == 2)
		set_field(&val, 0x0, CM_CAMERRX_CTRL_CSI1_CTRLCLKEN_MASK);
	reg_write(ctx->dev->cm, CM_CTRL_CORE_CAMERRX_CONTROL, val);
}