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
struct devlink_health_reporter {int dummy; } ;
struct devlink_fmsg {int dummy; } ;
struct bnxt_fw_health {int dummy; } ;
struct bnxt {int /*<<< orphan*/  state; struct bnxt_fw_health* fw_health; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FW_HEALTH_REG ; 
 int /*<<< orphan*/  BNXT_FW_RESET_CNT_REG ; 
 int BNXT_FW_STATUS_HEALTHY ; 
 int /*<<< orphan*/  BNXT_STATE_IN_FW_RESET ; 
 int bnxt_fw_health_readl (struct bnxt*,int /*<<< orphan*/ ) ; 
 int devlink_fmsg_string_pair_put (struct devlink_fmsg*,char*,char*) ; 
 int devlink_fmsg_u32_pair_put (struct devlink_fmsg*,char*,int) ; 
 struct bnxt* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_fw_reporter_diagnose(struct devlink_health_reporter *reporter,
				     struct devlink_fmsg *fmsg)
{
	struct bnxt *bp = devlink_health_reporter_priv(reporter);
	struct bnxt_fw_health *health = bp->fw_health;
	u32 val, health_status;
	int rc;

	if (!health || test_bit(BNXT_STATE_IN_FW_RESET, &bp->state))
		return 0;

	val = bnxt_fw_health_readl(bp, BNXT_FW_HEALTH_REG);
	health_status = val & 0xffff;

	if (health_status < BNXT_FW_STATUS_HEALTHY) {
		rc = devlink_fmsg_string_pair_put(fmsg, "Description",
						  "Not yet completed initialization");
		if (rc)
			return rc;
	} else if (health_status > BNXT_FW_STATUS_HEALTHY) {
		rc = devlink_fmsg_string_pair_put(fmsg, "Description",
						  "Encountered fatal error and cannot recover");
		if (rc)
			return rc;
	}

	if (val >> 16) {
		rc = devlink_fmsg_u32_pair_put(fmsg, "Error code", val >> 16);
		if (rc)
			return rc;
	}

	val = bnxt_fw_health_readl(bp, BNXT_FW_RESET_CNT_REG);
	rc = devlink_fmsg_u32_pair_put(fmsg, "Reset count", val);
	if (rc)
		return rc;

	return 0;
}