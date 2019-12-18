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
struct ipu_di {int /*<<< orphan*/  clk_di_pixel; int /*<<< orphan*/  module; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_module_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ipu_di_disable(struct ipu_di *di)
{
	WARN_ON(IS_ERR(di->clk_di_pixel));

	ipu_module_disable(di->ipu, di->module);

	clk_disable_unprepare(di->clk_di_pixel);

	return 0;
}