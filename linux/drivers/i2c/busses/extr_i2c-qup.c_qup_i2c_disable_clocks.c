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
typedef  int /*<<< orphan*/  u32 ;
struct qup_i2c_dev {int /*<<< orphan*/  pclk; scalar_t__ base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUP_CLOCK_AUTO_GATE ; 
 scalar_t__ QUP_CONFIG ; 
 int /*<<< orphan*/  QUP_RESET_STATE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qup_i2c_change_state (struct qup_i2c_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void qup_i2c_disable_clocks(struct qup_i2c_dev *qup)
{
	u32 config;

	qup_i2c_change_state(qup, QUP_RESET_STATE);
	clk_disable_unprepare(qup->clk);
	config = readl(qup->base + QUP_CONFIG);
	config |= QUP_CLOCK_AUTO_GATE;
	writel(config, qup->base + QUP_CONFIG);
	clk_disable_unprepare(qup->pclk);
}