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
struct bdisp_dev {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int bdisp_m2m_suspend (struct bdisp_dev*) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct bdisp_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int bdisp_runtime_suspend(struct device *dev)
{
	struct bdisp_dev *bdisp = dev_get_drvdata(dev);
	int ret = bdisp_m2m_suspend(bdisp);

	if (!ret)
		clk_disable(bdisp->clock);

	return ret;
}