#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct coda_dev {TYPE_2__* devtype; } ;
struct TYPE_6__ {int codec_mode; int codec_mode_aux; } ;
struct TYPE_4__ {int paddr; } ;
struct coda_ctx {int bit_stream_param; int frm_dis_flg; int frame_mem_ctrl; int idx; TYPE_3__ params; TYPE_1__ workbuf; int /*<<< orphan*/  reg_idx; struct coda_dev* dev; } ;
struct TYPE_5__ {scalar_t__ product; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA7_REG_BIT_RUN_AUX_STD ; 
 int /*<<< orphan*/  CODA9_GDI_WPROT_ERR_CLR ; 
 int /*<<< orphan*/  CODA9_GDI_WPROT_RGN_EN ; 
 scalar_t__ CODA_7541 ; 
 scalar_t__ CODA_960 ; 
 scalar_t__ CODA_HX4 ; 
 int /*<<< orphan*/  CODA_REG_BIT_BIT_STREAM_PARAM ; 
 int /*<<< orphan*/  CODA_REG_BIT_BUSY ; 
 int CODA_REG_BIT_BUSY_FLAG ; 
 int /*<<< orphan*/  CODA_REG_BIT_FRAME_MEM_CTRL ; 
 int /*<<< orphan*/  CODA_REG_BIT_FRM_DIS_FLG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODA_REG_BIT_RUN_COD_STD ; 
 int /*<<< orphan*/  CODA_REG_BIT_RUN_COMMAND ; 
 int /*<<< orphan*/  CODA_REG_BIT_RUN_INDEX ; 
 int /*<<< orphan*/  CODA_REG_BIT_WORK_BUF_ADDR ; 
 int /*<<< orphan*/  coda_write (struct coda_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_coda_bit_run (struct coda_ctx*,int) ; 

__attribute__((used)) static void coda_command_async(struct coda_ctx *ctx, int cmd)
{
	struct coda_dev *dev = ctx->dev;

	if (dev->devtype->product == CODA_HX4 ||
	    dev->devtype->product == CODA_7541 ||
	    dev->devtype->product == CODA_960) {
		/* Restore context related registers to CODA */
		coda_write(dev, ctx->bit_stream_param,
				CODA_REG_BIT_BIT_STREAM_PARAM);
		coda_write(dev, ctx->frm_dis_flg,
				CODA_REG_BIT_FRM_DIS_FLG(ctx->reg_idx));
		coda_write(dev, ctx->frame_mem_ctrl,
				CODA_REG_BIT_FRAME_MEM_CTRL);
		coda_write(dev, ctx->workbuf.paddr, CODA_REG_BIT_WORK_BUF_ADDR);
	}

	if (dev->devtype->product == CODA_960) {
		coda_write(dev, 1, CODA9_GDI_WPROT_ERR_CLR);
		coda_write(dev, 0, CODA9_GDI_WPROT_RGN_EN);
	}

	coda_write(dev, CODA_REG_BIT_BUSY_FLAG, CODA_REG_BIT_BUSY);

	coda_write(dev, ctx->idx, CODA_REG_BIT_RUN_INDEX);
	coda_write(dev, ctx->params.codec_mode, CODA_REG_BIT_RUN_COD_STD);
	coda_write(dev, ctx->params.codec_mode_aux, CODA7_REG_BIT_RUN_AUX_STD);

	trace_coda_bit_run(ctx, cmd);

	coda_write(dev, cmd, CODA_REG_BIT_RUN_COMMAND);
}