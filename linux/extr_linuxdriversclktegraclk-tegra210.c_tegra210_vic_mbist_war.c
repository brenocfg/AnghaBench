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
typedef  int u32 ;
struct tegra210_domain_mbist_war {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int GENMASK (int,int) ; 
 scalar_t__ LVL2_CLK_GATE_OVRE ; 
 scalar_t__ NV_PVIC_THI_SLCG_OVERRIDE_LOW ; 
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  fence_udelay (int,scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ vic_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tegra210_vic_mbist_war(struct tegra210_domain_mbist_war *mbist)
{
	u32 ovre, val;

	ovre = readl_relaxed(clk_base + LVL2_CLK_GATE_OVRE);
	writel_relaxed(ovre | BIT(5), clk_base + LVL2_CLK_GATE_OVRE);
	fence_udelay(1, clk_base);

	val = readl_relaxed(vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);
	writel_relaxed(val | BIT(0) | GENMASK(7, 2) | BIT(24),
			vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);
	fence_udelay(1, vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);

	writel_relaxed(val, vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);
	readl(vic_base + NV_PVIC_THI_SLCG_OVERRIDE_LOW);

	writel_relaxed(ovre, clk_base + LVL2_CLK_GATE_OVRE);
	fence_udelay(1, clk_base);
}