#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  osb_blend1_size; int /*<<< orphan*/  osb_blend0_size; int /*<<< orphan*/  osd_blend_din0_scope_v; int /*<<< orphan*/  osd_blend_din0_scope_h; } ;
struct meson_drm {scalar_t__ io_base; TYPE_1__ viu; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD1_BLEND_SRC_CTRL ; 
 int /*<<< orphan*/  VIU_OSD_BLEND_BLEND0_SIZE ; 
 int /*<<< orphan*/  VIU_OSD_BLEND_BLEND1_SIZE ; 
 int /*<<< orphan*/  VIU_OSD_BLEND_DIN0_SCOPE_H ; 
 int /*<<< orphan*/  VIU_OSD_BLEND_DIN0_SCOPE_V ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_g12a_crtc_enable_osd1(struct meson_drm *priv)
{
	writel_relaxed(priv->viu.osd_blend_din0_scope_h,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_DIN0_SCOPE_H));
	writel_relaxed(priv->viu.osd_blend_din0_scope_v,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_DIN0_SCOPE_V));
	writel_relaxed(priv->viu.osb_blend0_size,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_BLEND0_SIZE));
	writel_relaxed(priv->viu.osb_blend1_size,
		       priv->io_base +
		       _REG(VIU_OSD_BLEND_BLEND1_SIZE));
	writel_bits_relaxed(3 << 8, 3 << 8,
			    priv->io_base + _REG(OSD1_BLEND_SRC_CTRL));
}