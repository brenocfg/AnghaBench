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
struct iss_csi2_device {int /*<<< orphan*/  regs1; int /*<<< orphan*/  iss; } ;
struct iss_csi2_ctx_cfg {int virtual_id; int format_id; int alpha; int ping_addr; int pong_addr; int /*<<< orphan*/  ctxnum; int /*<<< orphan*/  data_offset; scalar_t__ dpcm_predictor; scalar_t__ dpcm_decompress; scalar_t__ checksum_enabled; scalar_t__ eol_enabled; scalar_t__ eof_enabled; scalar_t__ frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_CTX_CTRL1 (int /*<<< orphan*/ ) ; 
 int CSI2_CTX_CTRL1_CS_EN ; 
 int CSI2_CTX_CTRL1_EOF_EN ; 
 int CSI2_CTX_CTRL1_EOL_EN ; 
 int /*<<< orphan*/  CSI2_CTX_CTRL2 (int /*<<< orphan*/ ) ; 
 int CSI2_CTX_CTRL2_DPCM_PRED ; 
 int CSI2_CTX_CTRL2_FORMAT_SHIFT ; 
 int CSI2_CTX_CTRL2_USER_DEF_MAP_SHIFT ; 
 int CSI2_CTX_CTRL2_VIRTUAL_ID_SHIFT ; 
 int /*<<< orphan*/  CSI2_CTX_CTRL3 (int /*<<< orphan*/ ) ; 
 int CSI2_CTX_CTRL3_ALPHA_SHIFT ; 
 int /*<<< orphan*/  CSI2_CTX_DAT_OFST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSI2_CTX_DAT_OFST_MASK ; 
 int /*<<< orphan*/  CSI2_CTX_PING_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSI2_CTX_PONG_ADDR (int /*<<< orphan*/ ) ; 
 scalar_t__ is_usr_def_mapping (int) ; 
 int /*<<< orphan*/  iss_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csi2_ctx_config(struct iss_csi2_device *csi2,
			    struct iss_csi2_ctx_cfg *ctx)
{
	u32 reg = 0;

	ctx->frame = 0;

	/* Set up CSI2_CTx_CTRL1 */
	if (ctx->eof_enabled)
		reg = CSI2_CTX_CTRL1_EOF_EN;

	if (ctx->eol_enabled)
		reg |= CSI2_CTX_CTRL1_EOL_EN;

	if (ctx->checksum_enabled)
		reg |= CSI2_CTX_CTRL1_CS_EN;

	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTX_CTRL1(ctx->ctxnum), reg);

	/* Set up CSI2_CTx_CTRL2 */
	reg = ctx->virtual_id << CSI2_CTX_CTRL2_VIRTUAL_ID_SHIFT;
	reg |= ctx->format_id << CSI2_CTX_CTRL2_FORMAT_SHIFT;

	if (ctx->dpcm_decompress && ctx->dpcm_predictor)
		reg |= CSI2_CTX_CTRL2_DPCM_PRED;

	if (is_usr_def_mapping(ctx->format_id))
		reg |= 2 << CSI2_CTX_CTRL2_USER_DEF_MAP_SHIFT;

	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTX_CTRL2(ctx->ctxnum), reg);

	/* Set up CSI2_CTx_CTRL3 */
	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTX_CTRL3(ctx->ctxnum),
		      ctx->alpha << CSI2_CTX_CTRL3_ALPHA_SHIFT);

	/* Set up CSI2_CTx_DAT_OFST */
	iss_reg_update(csi2->iss, csi2->regs1, CSI2_CTX_DAT_OFST(ctx->ctxnum),
		       CSI2_CTX_DAT_OFST_MASK, ctx->data_offset);

	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTX_PING_ADDR(ctx->ctxnum),
		      ctx->ping_addr);
	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTX_PONG_ADDR(ctx->ctxnum),
		      ctx->pong_addr);
}