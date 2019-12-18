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
struct bnxt_fw_reporter_ctx {unsigned long sp_event; } ;
struct bnxt_fw_health {int /*<<< orphan*/  fw_fatal_reporter; int /*<<< orphan*/  fw_reset_reporter; } ;
struct bnxt {int /*<<< orphan*/  state; struct bnxt_fw_health* fw_health; } ;

/* Variables and functions */
#define  BNXT_FW_EXCEPTION_SP_EVENT 129 
#define  BNXT_FW_RESET_NOTIFY_SP_EVENT 128 
 int /*<<< orphan*/  BNXT_STATE_FW_FATAL_COND ; 
 int /*<<< orphan*/  devlink_health_report (int /*<<< orphan*/ ,char*,struct bnxt_fw_reporter_ctx*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bnxt_devlink_health_report(struct bnxt *bp, unsigned long event)
{
	struct bnxt_fw_health *fw_health = bp->fw_health;
	struct bnxt_fw_reporter_ctx fw_reporter_ctx;

	if (!fw_health)
		return;

	fw_reporter_ctx.sp_event = event;
	switch (event) {
	case BNXT_FW_RESET_NOTIFY_SP_EVENT:
		if (test_bit(BNXT_STATE_FW_FATAL_COND, &bp->state)) {
			if (!fw_health->fw_fatal_reporter)
				return;

			devlink_health_report(fw_health->fw_fatal_reporter,
					      "FW fatal async event received",
					      &fw_reporter_ctx);
			return;
		}
		if (!fw_health->fw_reset_reporter)
			return;

		devlink_health_report(fw_health->fw_reset_reporter,
				      "FW non-fatal reset event received",
				      &fw_reporter_ctx);
		return;

	case BNXT_FW_EXCEPTION_SP_EVENT:
		if (!fw_health->fw_fatal_reporter)
			return;

		devlink_health_report(fw_health->fw_fatal_reporter,
				      "FW fatal error reported",
				      &fw_reporter_ctx);
		return;
	}
}