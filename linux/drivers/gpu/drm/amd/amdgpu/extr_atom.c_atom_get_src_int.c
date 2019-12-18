#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct atom_context {int reg_block; int io_mode; int* divmul; int data_block; int shift; int fb_base; int io_attr; int scratch_size_bytes; int* scratch; TYPE_2__* card; int /*<<< orphan*/ * iio; } ;
struct TYPE_6__ {int* ws; int /*<<< orphan*/ * ps; struct atom_context* ctx; } ;
typedef  TYPE_1__ atom_exec_context ;
struct TYPE_7__ {int (* reg_read ) (TYPE_2__*,int) ;int (* pll_read ) (TYPE_2__*,int) ;int (* mc_read ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
#define  ATOM_ARG_FB 155 
#define  ATOM_ARG_ID 154 
#define  ATOM_ARG_IMM 153 
#define  ATOM_ARG_MC 152 
#define  ATOM_ARG_PLL 151 
#define  ATOM_ARG_PS 150 
#define  ATOM_ARG_REG 149 
#define  ATOM_ARG_WS 148 
#define  ATOM_IO_MM 147 
#define  ATOM_IO_PCI 146 
#define  ATOM_IO_SYSIO 145 
#define  ATOM_SRC_BYTE0 144 
#define  ATOM_SRC_BYTE16 143 
#define  ATOM_SRC_BYTE24 142 
#define  ATOM_SRC_BYTE8 141 
#define  ATOM_SRC_DWORD 140 
#define  ATOM_SRC_WORD0 139 
#define  ATOM_SRC_WORD16 138 
#define  ATOM_SRC_WORD8 137 
#define  ATOM_WS_AND_MASK 136 
#define  ATOM_WS_ATTRIBUTES 135 
#define  ATOM_WS_DATAPTR 134 
#define  ATOM_WS_FB_WINDOW 133 
#define  ATOM_WS_OR_MASK 132 
#define  ATOM_WS_QUOTIENT 131 
#define  ATOM_WS_REGPTR 130 
#define  ATOM_WS_REMAINDER 129 
#define  ATOM_WS_SHIFT 128 
 int /*<<< orphan*/  DEBUG (char*,int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int U16 (int) ; 
 int U32 (int) ; 
 int U8 (int) ; 
 int* atom_arg_mask ; 
 int* atom_arg_shift ; 
 int atom_iio_execute (struct atom_context*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int stub1 (TYPE_2__*,int) ; 
 int stub2 (TYPE_2__*,int) ; 
 int stub3 (TYPE_2__*,int) ; 

__attribute__((used)) static uint32_t atom_get_src_int(atom_exec_context *ctx, uint8_t attr,
				 int *ptr, uint32_t *saved, int print)
{
	uint32_t idx, val = 0xCDCDCDCD, align, arg;
	struct atom_context *gctx = ctx->ctx;
	arg = attr & 7;
	align = (attr >> 3) & 7;
	switch (arg) {
	case ATOM_ARG_REG:
		idx = U16(*ptr);
		(*ptr) += 2;
		if (print)
			DEBUG("REG[0x%04X]", idx);
		idx += gctx->reg_block;
		switch (gctx->io_mode) {
		case ATOM_IO_MM:
			val = gctx->card->reg_read(gctx->card, idx);
			break;
		case ATOM_IO_PCI:
			pr_info("PCI registers are not implemented\n");
			return 0;
		case ATOM_IO_SYSIO:
			pr_info("SYSIO registers are not implemented\n");
			return 0;
		default:
			if (!(gctx->io_mode & 0x80)) {
				pr_info("Bad IO mode\n");
				return 0;
			}
			if (!gctx->iio[gctx->io_mode & 0x7F]) {
				pr_info("Undefined indirect IO read method %d\n",
					gctx->io_mode & 0x7F);
				return 0;
			}
			val =
			    atom_iio_execute(gctx,
					     gctx->iio[gctx->io_mode & 0x7F],
					     idx, 0);
		}
		break;
	case ATOM_ARG_PS:
		idx = U8(*ptr);
		(*ptr)++;
		/* get_unaligned_le32 avoids unaligned accesses from atombios
		 * tables, noticed on a DEC Alpha. */
		val = get_unaligned_le32((u32 *)&ctx->ps[idx]);
		if (print)
			DEBUG("PS[0x%02X,0x%04X]", idx, val);
		break;
	case ATOM_ARG_WS:
		idx = U8(*ptr);
		(*ptr)++;
		if (print)
			DEBUG("WS[0x%02X]", idx);
		switch (idx) {
		case ATOM_WS_QUOTIENT:
			val = gctx->divmul[0];
			break;
		case ATOM_WS_REMAINDER:
			val = gctx->divmul[1];
			break;
		case ATOM_WS_DATAPTR:
			val = gctx->data_block;
			break;
		case ATOM_WS_SHIFT:
			val = gctx->shift;
			break;
		case ATOM_WS_OR_MASK:
			val = 1 << gctx->shift;
			break;
		case ATOM_WS_AND_MASK:
			val = ~(1 << gctx->shift);
			break;
		case ATOM_WS_FB_WINDOW:
			val = gctx->fb_base;
			break;
		case ATOM_WS_ATTRIBUTES:
			val = gctx->io_attr;
			break;
		case ATOM_WS_REGPTR:
			val = gctx->reg_block;
			break;
		default:
			val = ctx->ws[idx];
		}
		break;
	case ATOM_ARG_ID:
		idx = U16(*ptr);
		(*ptr) += 2;
		if (print) {
			if (gctx->data_block)
				DEBUG("ID[0x%04X+%04X]", idx, gctx->data_block);
			else
				DEBUG("ID[0x%04X]", idx);
		}
		val = U32(idx + gctx->data_block);
		break;
	case ATOM_ARG_FB:
		idx = U8(*ptr);
		(*ptr)++;
		if ((gctx->fb_base + (idx * 4)) > gctx->scratch_size_bytes) {
			DRM_ERROR("ATOM: fb read beyond scratch region: %d vs. %d\n",
				  gctx->fb_base + (idx * 4), gctx->scratch_size_bytes);
			val = 0;
		} else
			val = gctx->scratch[(gctx->fb_base / 4) + idx];
		if (print)
			DEBUG("FB[0x%02X]", idx);
		break;
	case ATOM_ARG_IMM:
		switch (align) {
		case ATOM_SRC_DWORD:
			val = U32(*ptr);
			(*ptr) += 4;
			if (print)
				DEBUG("IMM 0x%08X\n", val);
			return val;
		case ATOM_SRC_WORD0:
		case ATOM_SRC_WORD8:
		case ATOM_SRC_WORD16:
			val = U16(*ptr);
			(*ptr) += 2;
			if (print)
				DEBUG("IMM 0x%04X\n", val);
			return val;
		case ATOM_SRC_BYTE0:
		case ATOM_SRC_BYTE8:
		case ATOM_SRC_BYTE16:
		case ATOM_SRC_BYTE24:
			val = U8(*ptr);
			(*ptr)++;
			if (print)
				DEBUG("IMM 0x%02X\n", val);
			return val;
		}
		return 0;
	case ATOM_ARG_PLL:
		idx = U8(*ptr);
		(*ptr)++;
		if (print)
			DEBUG("PLL[0x%02X]", idx);
		val = gctx->card->pll_read(gctx->card, idx);
		break;
	case ATOM_ARG_MC:
		idx = U8(*ptr);
		(*ptr)++;
		if (print)
			DEBUG("MC[0x%02X]", idx);
		val = gctx->card->mc_read(gctx->card, idx);
		break;
	}
	if (saved)
		*saved = val;
	val &= atom_arg_mask[align];
	val >>= atom_arg_shift[align];
	if (print)
		switch (align) {
		case ATOM_SRC_DWORD:
			DEBUG(".[31:0] -> 0x%08X\n", val);
			break;
		case ATOM_SRC_WORD0:
			DEBUG(".[15:0] -> 0x%04X\n", val);
			break;
		case ATOM_SRC_WORD8:
			DEBUG(".[23:8] -> 0x%04X\n", val);
			break;
		case ATOM_SRC_WORD16:
			DEBUG(".[31:16] -> 0x%04X\n", val);
			break;
		case ATOM_SRC_BYTE0:
			DEBUG(".[7:0] -> 0x%02X\n", val);
			break;
		case ATOM_SRC_BYTE8:
			DEBUG(".[15:8] -> 0x%02X\n", val);
			break;
		case ATOM_SRC_BYTE16:
			DEBUG(".[23:16] -> 0x%02X\n", val);
			break;
		case ATOM_SRC_BYTE24:
			DEBUG(".[31:24] -> 0x%02X\n", val);
			break;
		}
	return val;
}