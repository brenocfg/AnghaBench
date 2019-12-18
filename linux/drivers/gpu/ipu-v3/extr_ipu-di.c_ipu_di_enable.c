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
struct ipu_di {int /*<<< orphan*/  module; int /*<<< orphan*/  ipu; int /*<<< orphan*/  clk_di_pixel; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_module_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipu_di_enable(struct ipu_di *di)
{
	int ret;

	WARN_ON(IS_ERR(di->clk_di_pixel));

	ret = clk_prepare_enable(di->clk_di_pixel);
	if (ret)
		return ret;

	ipu_module_enable(di->ipu, di->module);

	return 0;
}