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
struct dce_hwseq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN0_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN0_POWER_FORCEON ; 
 int /*<<< orphan*/  DOMAIN1_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN1_POWER_FORCEON ; 
 int /*<<< orphan*/  DOMAIN2_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN2_POWER_FORCEON ; 
 int /*<<< orphan*/  DOMAIN3_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN3_POWER_FORCEON ; 
 int /*<<< orphan*/  DOMAIN4_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN4_POWER_FORCEON ; 
 int /*<<< orphan*/  DOMAIN5_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN5_POWER_FORCEON ; 
 int /*<<< orphan*/  DOMAIN6_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN6_POWER_FORCEON ; 
 int /*<<< orphan*/  DOMAIN7_PG_CONFIG ; 
 int /*<<< orphan*/  DOMAIN7_POWER_FORCEON ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dcn10_enable_power_gating_plane(
	struct dce_hwseq *hws,
	bool enable)
{
	bool force_on = 1; /* disable power gating */

	if (enable)
		force_on = 0;

	/* DCHUBP0/1/2/3 */
	REG_UPDATE(DOMAIN0_PG_CONFIG, DOMAIN0_POWER_FORCEON, force_on);
	REG_UPDATE(DOMAIN2_PG_CONFIG, DOMAIN2_POWER_FORCEON, force_on);
	REG_UPDATE(DOMAIN4_PG_CONFIG, DOMAIN4_POWER_FORCEON, force_on);
	REG_UPDATE(DOMAIN6_PG_CONFIG, DOMAIN6_POWER_FORCEON, force_on);

	/* DPP0/1/2/3 */
	REG_UPDATE(DOMAIN1_PG_CONFIG, DOMAIN1_POWER_FORCEON, force_on);
	REG_UPDATE(DOMAIN3_PG_CONFIG, DOMAIN3_POWER_FORCEON, force_on);
	REG_UPDATE(DOMAIN5_PG_CONFIG, DOMAIN5_POWER_FORCEON, force_on);
	REG_UPDATE(DOMAIN7_PG_CONFIG, DOMAIN7_POWER_FORCEON, force_on);
}