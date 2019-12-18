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
struct vop {int /*<<< orphan*/  dclk; int /*<<< orphan*/  hclk; int /*<<< orphan*/  aclk; scalar_t__ rgb; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct vop* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  rockchip_rgb_fini (scalar_t__) ; 
 int /*<<< orphan*/  vop_destroy_crtc (struct vop*) ; 

__attribute__((used)) static void vop_unbind(struct device *dev, struct device *master, void *data)
{
	struct vop *vop = dev_get_drvdata(dev);

	if (vop->rgb)
		rockchip_rgb_fini(vop->rgb);

	pm_runtime_disable(dev);
	vop_destroy_crtc(vop);

	clk_unprepare(vop->aclk);
	clk_unprepare(vop->hclk);
	clk_unprepare(vop->dclk);
}