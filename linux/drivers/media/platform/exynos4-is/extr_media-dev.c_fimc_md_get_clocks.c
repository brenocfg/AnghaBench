#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fimc_md {struct clk** wbclk; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  use_isp; TYPE_2__* camclk; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  clk_name ;
struct TYPE_4__ {struct clk* clock; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 size_t CLK_IDX_WB_A ; 
 int CLK_IDX_WB_B ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FIMC_MAX_CAMCLKS ; 
 int FIMC_MAX_WBCLKS ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*) ; 
 int /*<<< orphan*/  fimc_md_put_clocks (struct fimc_md*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int fimc_md_get_clocks(struct fimc_md *fmd)
{
	struct device *dev = &fmd->pdev->dev;
	char clk_name[32];
	struct clk *clock;
	int i, ret = 0;

	for (i = 0; i < FIMC_MAX_CAMCLKS; i++)
		fmd->camclk[i].clock = ERR_PTR(-EINVAL);

	for (i = 0; i < FIMC_MAX_CAMCLKS; i++) {
		snprintf(clk_name, sizeof(clk_name), "sclk_cam%u", i);
		clock = clk_get(dev, clk_name);

		if (IS_ERR(clock)) {
			dev_err(dev, "Failed to get clock: %s\n", clk_name);
			ret = PTR_ERR(clock);
			break;
		}
		fmd->camclk[i].clock = clock;
	}
	if (ret)
		fimc_md_put_clocks(fmd);

	if (!fmd->use_isp)
		return 0;
	/*
	 * For now get only PIXELASYNCM1 clock (Writeback B/ISP),
	 * leave PIXELASYNCM0 out for the LCD Writeback driver.
	 */
	fmd->wbclk[CLK_IDX_WB_A] = ERR_PTR(-EINVAL);

	for (i = CLK_IDX_WB_B; i < FIMC_MAX_WBCLKS; i++) {
		snprintf(clk_name, sizeof(clk_name), "pxl_async%u", i);
		clock = clk_get(dev, clk_name);
		if (IS_ERR(clock)) {
			v4l2_err(&fmd->v4l2_dev, "Failed to get clock: %s\n",
				  clk_name);
			ret = PTR_ERR(clock);
			break;
		}
		fmd->wbclk[i] = clock;
	}
	if (ret)
		fimc_md_put_clocks(fmd);

	return ret;
}