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
struct ipu_dc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DC_WR_CH_CONF ; 
 int /*<<< orphan*/  DC_WR_CH_CONF_PROG_TYPE_NORMAL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void ipu_dc_enable_channel(struct ipu_dc *dc)
{
	u32 reg;

	reg = readl(dc->base + DC_WR_CH_CONF);
	reg |= DC_WR_CH_CONF_PROG_TYPE_NORMAL;
	writel(reg, dc->base + DC_WR_CH_CONF);
}