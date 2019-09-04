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
struct meson_drm {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPP_OSD_HSC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_SC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_VSC_CTRL0 ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void meson_vpp_disable_interlace_vscaler_osd1(struct meson_drm *priv)
{
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_SC_CTRL0));
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_VSC_CTRL0));
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_HSC_CTRL0));
}