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
struct venc_device {scalar_t__ tv_dac_clk; TYPE_1__* dss; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (scalar_t__) ; 
 struct venc_device* dev_get_drvdata (struct device*) ; 
 int dispc_runtime_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int venc_runtime_resume(struct device *dev)
{
	struct venc_device *venc = dev_get_drvdata(dev);
	int r;

	r = dispc_runtime_get(venc->dss->dispc);
	if (r < 0)
		return r;

	if (venc->tv_dac_clk)
		clk_prepare_enable(venc->tv_dac_clk);

	return 0;
}