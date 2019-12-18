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
typedef  scalar_t__ u32 ;
struct bnxt_fw_health {scalar_t__ last_fw_heartbeat; scalar_t__ last_fw_reset_cnt; } ;
struct bnxt {struct bnxt_fw_health* fw_health; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FW_HEARTBEAT_REG ; 
 int /*<<< orphan*/  BNXT_FW_RESET_CNT_REG ; 
 scalar_t__ bnxt_fw_health_readl (struct bnxt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_bnxt_fw_ok(struct bnxt *bp)
{
	struct bnxt_fw_health *fw_health = bp->fw_health;
	bool no_heartbeat = false, has_reset = false;
	u32 val;

	val = bnxt_fw_health_readl(bp, BNXT_FW_HEARTBEAT_REG);
	if (val == fw_health->last_fw_heartbeat)
		no_heartbeat = true;

	val = bnxt_fw_health_readl(bp, BNXT_FW_RESET_CNT_REG);
	if (val != fw_health->last_fw_reset_cnt)
		has_reset = true;

	if (!no_heartbeat && has_reset)
		return true;

	return false;
}