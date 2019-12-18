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
struct tegra_sor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOR_SUPER_STATE0 ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sor_super_update(struct tegra_sor *sor)
{
	tegra_sor_writel(sor, 0, SOR_SUPER_STATE0);
	tegra_sor_writel(sor, 1, SOR_SUPER_STATE0);
	tegra_sor_writel(sor, 0, SOR_SUPER_STATE0);
}