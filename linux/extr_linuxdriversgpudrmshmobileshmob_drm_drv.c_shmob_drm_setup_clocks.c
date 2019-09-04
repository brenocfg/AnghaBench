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
struct shmob_drm_device {struct clk* clock; int /*<<< orphan*/  dev; int /*<<< orphan*/  lddckr; } ;
struct clk {int dummy; } ;
typedef  enum shmob_drm_clk_source { ____Placeholder_shmob_drm_clk_source } shmob_drm_clk_source ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  LDDCKR_ICKSEL_BUS ; 
 int /*<<< orphan*/  LDDCKR_ICKSEL_HDMI ; 
 int /*<<< orphan*/  LDDCKR_ICKSEL_MIPI ; 
 int PTR_ERR (struct clk*) ; 
#define  SHMOB_DRM_CLK_BUS 130 
#define  SHMOB_DRM_CLK_EXTERNAL 129 
#define  SHMOB_DRM_CLK_PERIPHERAL 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int shmob_drm_setup_clocks(struct shmob_drm_device *sdev,
					    enum shmob_drm_clk_source clksrc)
{
	struct clk *clk;
	char *clkname;

	switch (clksrc) {
	case SHMOB_DRM_CLK_BUS:
		clkname = "bus_clk";
		sdev->lddckr = LDDCKR_ICKSEL_BUS;
		break;
	case SHMOB_DRM_CLK_PERIPHERAL:
		clkname = "peripheral_clk";
		sdev->lddckr = LDDCKR_ICKSEL_MIPI;
		break;
	case SHMOB_DRM_CLK_EXTERNAL:
		clkname = NULL;
		sdev->lddckr = LDDCKR_ICKSEL_HDMI;
		break;
	default:
		return -EINVAL;
	}

	clk = devm_clk_get(sdev->dev, clkname);
	if (IS_ERR(clk)) {
		dev_err(sdev->dev, "cannot get dot clock %s\n", clkname);
		return PTR_ERR(clk);
	}

	sdev->clock = clk;
	return 0;
}