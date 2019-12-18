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
struct cdn_dp_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ SW_CLK_H ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

void cdn_dp_set_fw_clk(struct cdn_dp_device *dp, unsigned long clk)
{
	writel(clk / 1000000, dp->regs + SW_CLK_H);
}