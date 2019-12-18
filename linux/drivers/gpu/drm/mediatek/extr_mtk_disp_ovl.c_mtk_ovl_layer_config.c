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
struct mtk_plane_pending_state {unsigned int addr; int pitch; unsigned int format; int y; int x; int height; int width; scalar_t__ enable; } ;
struct mtk_plane_state {struct mtk_plane_pending_state pending; } ;
struct mtk_disp_ovl {int dummy; } ;
struct mtk_ddp_comp {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DISP_REG_OVL_ADDR (struct mtk_disp_ovl*,unsigned int) ; 
 scalar_t__ DISP_REG_OVL_CON (unsigned int) ; 
 scalar_t__ DISP_REG_OVL_OFFSET (unsigned int) ; 
 scalar_t__ DISP_REG_OVL_PITCH (unsigned int) ; 
 scalar_t__ DISP_REG_OVL_SRC_SIZE (unsigned int) ; 
 unsigned int OVL_CON_AEN ; 
 unsigned int OVL_CON_ALPHA ; 
 struct mtk_disp_ovl* comp_to_ovl (struct mtk_ddp_comp*) ; 
 int /*<<< orphan*/  mtk_ovl_layer_off (struct mtk_ddp_comp*,unsigned int) ; 
 int /*<<< orphan*/  mtk_ovl_layer_on (struct mtk_ddp_comp*,unsigned int) ; 
 unsigned int ovl_fmt_convert (struct mtk_disp_ovl*,unsigned int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void mtk_ovl_layer_config(struct mtk_ddp_comp *comp, unsigned int idx,
				 struct mtk_plane_state *state)
{
	struct mtk_disp_ovl *ovl = comp_to_ovl(comp);
	struct mtk_plane_pending_state *pending = &state->pending;
	unsigned int addr = pending->addr;
	unsigned int pitch = pending->pitch & 0xffff;
	unsigned int fmt = pending->format;
	unsigned int offset = (pending->y << 16) | pending->x;
	unsigned int src_size = (pending->height << 16) | pending->width;
	unsigned int con;

	if (!pending->enable)
		mtk_ovl_layer_off(comp, idx);

	con = ovl_fmt_convert(ovl, fmt);
	if (idx != 0)
		con |= OVL_CON_AEN | OVL_CON_ALPHA;

	writel_relaxed(con, comp->regs + DISP_REG_OVL_CON(idx));
	writel_relaxed(pitch, comp->regs + DISP_REG_OVL_PITCH(idx));
	writel_relaxed(src_size, comp->regs + DISP_REG_OVL_SRC_SIZE(idx));
	writel_relaxed(offset, comp->regs + DISP_REG_OVL_OFFSET(idx));
	writel_relaxed(addr, comp->regs + DISP_REG_OVL_ADDR(ovl, idx));

	if (pending->enable)
		mtk_ovl_layer_on(comp, idx);
}