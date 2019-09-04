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
 int bdisp_m2m_resume (struct bdisp_dev*) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct bdisp_dev* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int bdisp_runtime_resume(struct device *dev)
{
	struct bdisp_dev *bdisp = dev_get_drvdata(dev);
	int ret = clk_enable(bdisp->clock);

	if (ret)
		return ret;

	return bdisp_m2m_resume(bdisp);
}