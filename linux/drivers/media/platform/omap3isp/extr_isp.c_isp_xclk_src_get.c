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
struct of_phandle_args {unsigned int* args; } ;
struct isp_device {TYPE_1__* xclks; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {struct clk* clk; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk *isp_xclk_src_get(struct of_phandle_args *clkspec, void *data)
{
	unsigned int idx = clkspec->args[0];
	struct isp_device *isp = data;

	if (idx >= ARRAY_SIZE(isp->xclks))
		return ERR_PTR(-ENOENT);

	return isp->xclks[idx].clk;
}