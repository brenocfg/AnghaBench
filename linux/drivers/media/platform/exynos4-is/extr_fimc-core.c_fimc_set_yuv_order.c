#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* fmt; } ;
struct TYPE_6__ {TYPE_1__* fmt; } ;
struct fimc_ctx {int /*<<< orphan*/  out_order_1p; TYPE_4__ d_frame; int /*<<< orphan*/  in_order_1p; TYPE_2__ s_frame; void* out_order_2p; void* in_order_2p; } ;
struct TYPE_7__ {int color; } ;
struct TYPE_5__ {int color; } ;

/* Variables and functions */
#define  FIMC_FMT_CBYCRY422 131 
#define  FIMC_FMT_CRYCBY422 130 
#define  FIMC_FMT_YCBYCR422 129 
#define  FIMC_FMT_YCRYCB422 128 
 void* FIMC_REG_CIOCTRL_ORDER422_2P_LSB_CRCB ; 
 int /*<<< orphan*/  FIMC_REG_CIOCTRL_ORDER422_CBYCRY ; 
 int /*<<< orphan*/  FIMC_REG_CIOCTRL_ORDER422_CRYCBY ; 
 int /*<<< orphan*/  FIMC_REG_CIOCTRL_ORDER422_YCBYCR ; 
 int /*<<< orphan*/  FIMC_REG_CIOCTRL_ORDER422_YCRYCB ; 
 int /*<<< orphan*/  FIMC_REG_MSCTRL_ORDER422_CBYCRY ; 
 int /*<<< orphan*/  FIMC_REG_MSCTRL_ORDER422_CRYCBY ; 
 int /*<<< orphan*/  FIMC_REG_MSCTRL_ORDER422_YCBYCR ; 
 int /*<<< orphan*/  FIMC_REG_MSCTRL_ORDER422_YCRYCB ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ) ; 

void fimc_set_yuv_order(struct fimc_ctx *ctx)
{
	/* The one only mode supported in SoC. */
	ctx->in_order_2p = FIMC_REG_CIOCTRL_ORDER422_2P_LSB_CRCB;
	ctx->out_order_2p = FIMC_REG_CIOCTRL_ORDER422_2P_LSB_CRCB;

	/* Set order for 1 plane input formats. */
	switch (ctx->s_frame.fmt->color) {
	case FIMC_FMT_YCRYCB422:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_YCRYCB;
		break;
	case FIMC_FMT_CBYCRY422:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_CBYCRY;
		break;
	case FIMC_FMT_CRYCBY422:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_CRYCBY;
		break;
	case FIMC_FMT_YCBYCR422:
	default:
		ctx->in_order_1p = FIMC_REG_MSCTRL_ORDER422_YCBYCR;
		break;
	}
	dbg("ctx->in_order_1p= %d", ctx->in_order_1p);

	switch (ctx->d_frame.fmt->color) {
	case FIMC_FMT_YCRYCB422:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_YCRYCB;
		break;
	case FIMC_FMT_CBYCRY422:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_CBYCRY;
		break;
	case FIMC_FMT_CRYCBY422:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_CRYCBY;
		break;
	case FIMC_FMT_YCBYCR422:
	default:
		ctx->out_order_1p = FIMC_REG_CIOCTRL_ORDER422_YCBYCR;
		break;
	}
	dbg("ctx->out_order_1p= %d", ctx->out_order_1p);
}