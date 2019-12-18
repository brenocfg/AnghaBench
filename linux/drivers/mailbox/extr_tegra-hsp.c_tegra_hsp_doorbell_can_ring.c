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
struct tegra_hsp_doorbell {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSP_DB_ENABLE ; 
 int /*<<< orphan*/  TEGRA_HSP_DB_MASTER_CCPLEX ; 
 int tegra_hsp_channel_readl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tegra_hsp_doorbell_can_ring(struct tegra_hsp_doorbell *db)
{
	u32 value;

	value = tegra_hsp_channel_readl(&db->channel, HSP_DB_ENABLE);

	return (value & BIT(TEGRA_HSP_DB_MASTER_CCPLEX)) != 0;
}