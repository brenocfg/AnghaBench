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
struct qup_i2c_dev {int /*<<< orphan*/  pclk; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qup_i2c_enable_clocks(struct qup_i2c_dev *qup)
{
	clk_prepare_enable(qup->clk);
	clk_prepare_enable(qup->pclk);
}