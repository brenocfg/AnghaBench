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
typedef  int u32 ;
struct tegra_soctherm {scalar_t__ regs; TYPE_1__* throt_cfgs; } ;
typedef  enum soctherm_throttle_id { ____Placeholder_soctherm_throttle_id } soctherm_throttle_id ;
struct TYPE_2__ {int gpu_throt_level; } ;

/* Variables and functions */
 int REG_SET_MASK (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THROTTLE_DEV_GPU ; 
 int THROT_LEVEL_TO_DEPTH (int) ; 
 scalar_t__ THROT_PSKIP_CTRL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_ENABLE_MASK ; 
 int /*<<< orphan*/  THROT_PSKIP_CTRL_VECT_GPU_MASK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void throttlectl_gpu_level_select(struct tegra_soctherm *ts,
					 enum soctherm_throttle_id throt)
{
	u32 r, level, throt_vect;

	level = ts->throt_cfgs[throt].gpu_throt_level;
	throt_vect = THROT_LEVEL_TO_DEPTH(level);
	r = readl(ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_GPU));
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_ENABLE_MASK, 1);
	r = REG_SET_MASK(r, THROT_PSKIP_CTRL_VECT_GPU_MASK, throt_vect);
	writel(r, ts->regs + THROT_PSKIP_CTRL(throt, THROTTLE_DEV_GPU));
}