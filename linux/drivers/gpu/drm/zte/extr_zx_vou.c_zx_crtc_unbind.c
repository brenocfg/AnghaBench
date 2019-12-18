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
struct zx_vou_hw {int /*<<< orphan*/  ppu_clk; int /*<<< orphan*/  axi_clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct zx_vou_hw* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void zx_crtc_unbind(struct device *dev, struct device *master,
			   void *data)
{
	struct zx_vou_hw *vou = dev_get_drvdata(dev);

	clk_disable_unprepare(vou->axi_clk);
	clk_disable_unprepare(vou->ppu_clk);
}