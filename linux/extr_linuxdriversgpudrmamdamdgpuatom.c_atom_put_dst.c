#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct atom_context {size_t reg_block; int io_mode; size_t* divmul; size_t data_block; size_t shift; size_t fb_base; size_t io_attr; size_t scratch_size_bytes; size_t* scratch; TYPE_2__* card; int /*<<< orphan*/ * iio; } ;
struct TYPE_7__ {size_t* ws; int /*<<< orphan*/ * ps; struct atom_context* ctx; } ;
typedef  TYPE_1__ atom_exec_context ;
struct TYPE_8__ {int /*<<< orphan*/  (* mc_write ) (TYPE_2__*,size_t,size_t) ;int /*<<< orphan*/  (* pll_write ) (TYPE_2__*,size_t,size_t) ;int /*<<< orphan*/  (* reg_write ) (TYPE_2__*,size_t,size_t) ;} ;

/* Variables and functions */
#define  ATOM_ARG_FB 153 
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
 int /*<<< orphan*/  DEBUG (char*,size_t) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,size_t,size_t) ; 
 size_t U16 (int) ; 
 size_t U8 (int) ; 
 size_t* atom_arg_mask ; 
 size_t* atom_arg_shift ; 
 size_t** atom_dst_to_src ; 
 int /*<<< orphan*/  atom_iio_execute (struct atom_context*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,size_t,size_t) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__*,size_t,size_t) ; 

__attribute__((used)) static void atom_put_dst(atom_exec_context *ctx, int arg, uint8_t attr,
			 int *ptr, uint32_t val, uint32_t saved)
{
	uint32_t align =
	    atom_dst_to_src[(attr >> 3) & 7][(attr >> 6) & 3], old_val =
	    val, idx;
	struct atom_context *gctx = ctx->ctx;
	old_val &= atom_arg_mask[align] >> atom_arg_shift[align];
	val <<= atom_arg_shift[align];
	val &= atom_arg_mask[align];
	saved &= ~atom_arg_mask[align];
	val |= saved;
	switch (arg) {
	case ATOM_ARG_REG:
		idx = U16(*ptr);
		(*ptr) += 2;
		DEBUG("REG[0x%04X]", idx);
		idx += gctx->reg_block;
		switch (gctx->io_mode) {
		case ATOM_IO_MM:
			if (idx == 0)
				gctx->card->reg_write(gctx->card, idx,
						      val << 2);
			else
				gctx->card->reg_write(gctx->card, idx, val);
			break;
		case ATOM_IO_PCI:
			pr_info("PCI registers are not implemented\n");
			return;
		case ATOM_IO_SYSIO:
			pr_info("SYSIO registers are not implemented\n");
			return;
		default:
			if (!(gctx->io_mode & 0x80)) {
				pr_info("Bad IO mode\n");
				return;
			}
			if (!gctx->iio[gctx->io_mode & 0xFF]) {
				pr_info("Undefined indirect IO write method %d\n",
					gctx->io_mode & 0x7F);
				return;
			}
			atom_iio_execute(gctx, gctx->iio[gctx->io_mode & 0xFF],
					 idx, val);
		}
		break;
	case ATOM_ARG_PS:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("PS[0x%02X]", idx);
		ctx->ps[idx] = cpu_to_le32(val);
		break;
	case ATOM_ARG_WS:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("WS[0x%02X]", idx);
		switch (idx) {
		case ATOM_WS_QUOTIENT:
			gctx->divmul[0] = val;
			break;
		case ATOM_WS_REMAINDER:
			gctx->divmul[1] = val;
			break;
		case ATOM_WS_DATAPTR:
			gctx->data_block = val;
			break;
		case ATOM_WS_SHIFT:
			gctx->shift = val;
			break;
		case ATOM_WS_OR_MASK:
		case ATOM_WS_AND_MASK:
			break;
		case ATOM_WS_FB_WINDOW:
			gctx->fb_base = val;
			break;
		case ATOM_WS_ATTRIBUTES:
			gctx->io_attr = val;
			break;
		case ATOM_WS_REGPTR:
			gctx->reg_block = val;
			break;
		default:
			ctx->ws[idx] = val;
		}
		break;
	case ATOM_ARG_FB:
		idx = U8(*ptr);
		(*ptr)++;
		if ((gctx->fb_base + (idx * 4)) > gctx->scratch_size_bytes) {
			DRM_ERROR("ATOM: fb write beyond scratch region: %d vs. %d\n",
				  gctx->fb_base + (idx * 4), gctx->scratch_size_bytes);
		} else
			gctx->scratch[(gctx->fb_base / 4) + idx] = val;
		DEBUG("FB[0x%02X]", idx);
		break;
	case ATOM_ARG_PLL:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("PLL[0x%02X]", idx);
		gctx->card->pll_write(gctx->card, idx, val);
		break;
	case ATOM_ARG_MC:
		idx = U8(*ptr);
		(*ptr)++;
		DEBUG("MC[0x%02X]", idx);
		gctx->card->mc_write(gctx->card, idx, val);
		return;
	}
	switch (align) {
	case ATOM_SRC_DWORD:
		DEBUG(".[31:0] <- 0x%08X\n", old_val);
		break;
	case ATOM_SRC_WORD0:
		DEBUG(".[15:0] <- 0x%04X\n", old_val);
		break;
	case ATOM_SRC_WORD8:
		DEBUG(".[23:8] <- 0x%04X\n", old_val);
		break;
	case ATOM_SRC_WORD16:
		DEBUG(".[31:16] <- 0x%04X\n", old_val);
		break;
	case ATOM_SRC_BYTE0:
		DEBUG(".[7:0] <- 0x%02X\n", old_val);
		break;
	case ATOM_SRC_BYTE8:
		DEBUG(".[15:8] <- 0x%02X\n", old_val);
		break;
	case ATOM_SRC_BYTE16:
		DEBUG(".[23:16] <- 0x%02X\n", old_val);
		break;
	case ATOM_SRC_BYTE24:
		DEBUG(".[31:24] <- 0x%02X\n", old_val);
		break;
	}
}