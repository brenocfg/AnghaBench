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
struct device {int dummy; } ;
struct clk {int dummy; } ;
struct armada_crtc {scalar_t__ base; struct clk** extclk; } ;

/* Variables and functions */
 int ADV_HWC32ARGB ; 
 int ADV_HWC32BLEND ; 
 int ADV_HWC32ENABLE ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ LCD_CFG_RDREG4F ; 
 scalar_t__ LCD_SPU_ADV_REG ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  armada_updatel (int,int,scalar_t__) ; 
 struct clk* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int armada510_crtc_init(struct armada_crtc *dcrtc, struct device *dev)
{
	struct clk *clk;

	clk = devm_clk_get(dev, "ext_ref_clk1");
	if (IS_ERR(clk))
		return PTR_ERR(clk) == -ENOENT ? -EPROBE_DEFER : PTR_ERR(clk);

	dcrtc->extclk[0] = clk;

	/* Lower the watermark so to eliminate jitter at higher bandwidths */
	armada_updatel(0x20, (1 << 11) | 0xff, dcrtc->base + LCD_CFG_RDREG4F);

	/* Initialise SPU register */
	writel_relaxed(ADV_HWC32ENABLE | ADV_HWC32ARGB | ADV_HWC32BLEND,
		       dcrtc->base + LCD_SPU_ADV_REG);

	return 0;
}