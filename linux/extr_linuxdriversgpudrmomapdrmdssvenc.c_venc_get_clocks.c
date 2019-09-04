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
struct venc_device {struct clk* tv_dac_clk; TYPE_1__* pdev; scalar_t__ requires_tv_dac_clk; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int venc_get_clocks(struct venc_device *venc)
{
	struct clk *clk;

	if (venc->requires_tv_dac_clk) {
		clk = devm_clk_get(&venc->pdev->dev, "tv_dac_clk");
		if (IS_ERR(clk)) {
			DSSERR("can't get tv_dac_clk\n");
			return PTR_ERR(clk);
		}
	} else {
		clk = NULL;
	}

	venc->tv_dac_clk = clk;

	return 0;
}