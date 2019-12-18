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
typedef  scalar_t__ uint64_t ;
typedef  unsigned int u32 ;
struct ipu_pre {unsigned int safe_window_end; unsigned int last_bufaddr; unsigned int buffer_paddr; scalar_t__ regs; } ;
struct drm_format_info {int* cpp; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int,int) ; 
 scalar_t__ DRM_FORMAT_MOD_LINEAR ; 
 scalar_t__ DRM_FORMAT_MOD_VIVANTE_SUPER_TILED ; 
 scalar_t__ IPU_PRE_CTRL ; 
 unsigned int IPU_PRE_CTRL_BLOCK_EN ; 
 unsigned int IPU_PRE_CTRL_ENABLE ; 
 unsigned int IPU_PRE_CTRL_EN_REPEAT ; 
 unsigned int IPU_PRE_CTRL_SDW_UPDATE ; 
 scalar_t__ IPU_PRE_CUR_BUF ; 
 scalar_t__ IPU_PRE_NEXT_BUF ; 
 scalar_t__ IPU_PRE_PREFETCH_ENG_CTRL ; 
 scalar_t__ IPU_PRE_PREFETCH_ENG_INPUT_SIZE ; 
 unsigned int IPU_PRE_PREFETCH_ENG_INPUT_SIZE_HEIGHT (unsigned int) ; 
 unsigned int IPU_PRE_PREFETCH_ENG_INPUT_SIZE_WIDTH (unsigned int) ; 
 scalar_t__ IPU_PRE_PREFETCH_ENG_PITCH ; 
 unsigned int IPU_PRE_PREFETCH_ENG_PITCH_Y (unsigned int) ; 
 unsigned int IPU_PRE_PREF_ENG_CTRL_INPUT_ACTIVE_BPP (unsigned int) ; 
 unsigned int IPU_PRE_PREF_ENG_CTRL_INPUT_PIXEL_FORMAT (int /*<<< orphan*/ ) ; 
 unsigned int IPU_PRE_PREF_ENG_CTRL_PREFETCH_EN ; 
 unsigned int IPU_PRE_PREF_ENG_CTRL_RD_NUM_BYTES (int) ; 
 unsigned int IPU_PRE_PREF_ENG_CTRL_SHIFT_BYPASS ; 
 scalar_t__ IPU_PRE_STORE_ENG_ADDR ; 
 scalar_t__ IPU_PRE_STORE_ENG_CTRL ; 
 unsigned int IPU_PRE_STORE_ENG_CTRL_OUTPUT_ACTIVE_BPP (unsigned int) ; 
 unsigned int IPU_PRE_STORE_ENG_CTRL_STORE_EN ; 
 unsigned int IPU_PRE_STORE_ENG_CTRL_WR_NUM_BYTES (int) ; 
 scalar_t__ IPU_PRE_STORE_ENG_PITCH ; 
 unsigned int IPU_PRE_STORE_ENG_PITCH_OUT_PITCH (unsigned int) ; 
 scalar_t__ IPU_PRE_STORE_ENG_SIZE ; 
 unsigned int IPU_PRE_STORE_ENG_SIZE_INPUT_HEIGHT (unsigned int) ; 
 unsigned int IPU_PRE_STORE_ENG_SIZE_INPUT_WIDTH (unsigned int) ; 
 scalar_t__ IPU_PRE_TPR_CTRL ; 
 unsigned int IPU_PRE_TPR_CTRL_TILE_FORMAT_16_BIT ; 
 unsigned int IPU_PRE_TPR_CTRL_TILE_FORMAT_MASK ; 
 unsigned int IPU_PRE_TPR_CTRL_TILE_FORMAT_SINGLE_BUF ; 
 unsigned int IPU_PRE_TPR_CTRL_TILE_FORMAT_SUPER_TILED ; 
 struct drm_format_info* drm_format_info (unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

void ipu_pre_configure(struct ipu_pre *pre, unsigned int width,
		       unsigned int height, unsigned int stride, u32 format,
		       uint64_t modifier, unsigned int bufaddr)
{
	const struct drm_format_info *info = drm_format_info(format);
	u32 active_bpp = info->cpp[0] >> 1;
	u32 val;

	/* calculate safe window for ctrl register updates */
	if (modifier == DRM_FORMAT_MOD_LINEAR)
		pre->safe_window_end = height - 2;
	else
		pre->safe_window_end = DIV_ROUND_UP(height, 4) - 1;

	writel(bufaddr, pre->regs + IPU_PRE_CUR_BUF);
	writel(bufaddr, pre->regs + IPU_PRE_NEXT_BUF);
	pre->last_bufaddr = bufaddr;

	val = IPU_PRE_PREF_ENG_CTRL_INPUT_PIXEL_FORMAT(0) |
	      IPU_PRE_PREF_ENG_CTRL_INPUT_ACTIVE_BPP(active_bpp) |
	      IPU_PRE_PREF_ENG_CTRL_RD_NUM_BYTES(4) |
	      IPU_PRE_PREF_ENG_CTRL_SHIFT_BYPASS |
	      IPU_PRE_PREF_ENG_CTRL_PREFETCH_EN;
	writel(val, pre->regs + IPU_PRE_PREFETCH_ENG_CTRL);

	val = IPU_PRE_PREFETCH_ENG_INPUT_SIZE_WIDTH(width) |
	      IPU_PRE_PREFETCH_ENG_INPUT_SIZE_HEIGHT(height);
	writel(val, pre->regs + IPU_PRE_PREFETCH_ENG_INPUT_SIZE);

	val = IPU_PRE_PREFETCH_ENG_PITCH_Y(stride);
	writel(val, pre->regs + IPU_PRE_PREFETCH_ENG_PITCH);

	val = IPU_PRE_STORE_ENG_CTRL_OUTPUT_ACTIVE_BPP(active_bpp) |
	      IPU_PRE_STORE_ENG_CTRL_WR_NUM_BYTES(4) |
	      IPU_PRE_STORE_ENG_CTRL_STORE_EN;
	writel(val, pre->regs + IPU_PRE_STORE_ENG_CTRL);

	val = IPU_PRE_STORE_ENG_SIZE_INPUT_WIDTH(width) |
	      IPU_PRE_STORE_ENG_SIZE_INPUT_HEIGHT(height);
	writel(val, pre->regs + IPU_PRE_STORE_ENG_SIZE);

	val = IPU_PRE_STORE_ENG_PITCH_OUT_PITCH(stride);
	writel(val, pre->regs + IPU_PRE_STORE_ENG_PITCH);

	writel(pre->buffer_paddr, pre->regs + IPU_PRE_STORE_ENG_ADDR);

	val = readl(pre->regs + IPU_PRE_TPR_CTRL);
	val &= ~IPU_PRE_TPR_CTRL_TILE_FORMAT_MASK;
	if (modifier != DRM_FORMAT_MOD_LINEAR) {
		/* only support single buffer formats for now */
		val |= IPU_PRE_TPR_CTRL_TILE_FORMAT_SINGLE_BUF;
		if (modifier == DRM_FORMAT_MOD_VIVANTE_SUPER_TILED)
			val |= IPU_PRE_TPR_CTRL_TILE_FORMAT_SUPER_TILED;
		if (info->cpp[0] == 2)
			val |= IPU_PRE_TPR_CTRL_TILE_FORMAT_16_BIT;
	}
	writel(val, pre->regs + IPU_PRE_TPR_CTRL);

	val = readl(pre->regs + IPU_PRE_CTRL);
	val |= IPU_PRE_CTRL_EN_REPEAT | IPU_PRE_CTRL_ENABLE |
	       IPU_PRE_CTRL_SDW_UPDATE;
	if (modifier == DRM_FORMAT_MOD_LINEAR)
		val &= ~IPU_PRE_CTRL_BLOCK_EN;
	else
		val |= IPU_PRE_CTRL_BLOCK_EN;
	writel(val, pre->regs + IPU_PRE_CTRL);
}