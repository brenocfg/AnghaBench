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
typedef  scalar_t__ u32 ;
struct rockchip_lvds {scalar_t__ output; TYPE_1__* soc_data; scalar_t__ regs; } ;
struct TYPE_2__ {scalar_t__ ch1_offset; } ;

/* Variables and functions */
 scalar_t__ DISPLAY_OUTPUT_LVDS ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void lvds_writel(struct rockchip_lvds *lvds, u32 offset, u32 val)
{
	writel_relaxed(val, lvds->regs + offset);
	if (lvds->output == DISPLAY_OUTPUT_LVDS)
		return;
	writel_relaxed(val, lvds->regs + offset + lvds->soc_data->ch1_offset);
}