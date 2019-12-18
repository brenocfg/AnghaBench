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
struct bnxt_fw_health {int /*<<< orphan*/ * fw_fatal_reporter; int /*<<< orphan*/ * fw_reset_reporter; int /*<<< orphan*/ * fw_reporter; } ;
struct bnxt {int /*<<< orphan*/  dev; int /*<<< orphan*/  dl; struct bnxt_fw_health* fw_health; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_dl_fw_fatal_reporter_ops ; 
 int /*<<< orphan*/  bnxt_dl_fw_reporter_ops ; 
 int /*<<< orphan*/  bnxt_dl_fw_reset_reporter_ops ; 
 void* devlink_health_reporter_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct bnxt*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_dl_fw_reporters_create(struct bnxt *bp)
{
	struct bnxt_fw_health *health = bp->fw_health;

	if (!health)
		return;

	health->fw_reporter =
		devlink_health_reporter_create(bp->dl, &bnxt_dl_fw_reporter_ops,
					       0, false, bp);
	if (IS_ERR(health->fw_reporter)) {
		netdev_warn(bp->dev, "Failed to create FW health reporter, rc = %ld\n",
			    PTR_ERR(health->fw_reporter));
		health->fw_reporter = NULL;
	}

	health->fw_reset_reporter =
		devlink_health_reporter_create(bp->dl,
					       &bnxt_dl_fw_reset_reporter_ops,
					       0, true, bp);
	if (IS_ERR(health->fw_reset_reporter)) {
		netdev_warn(bp->dev, "Failed to create FW fatal health reporter, rc = %ld\n",
			    PTR_ERR(health->fw_reset_reporter));
		health->fw_reset_reporter = NULL;
	}

	health->fw_fatal_reporter =
		devlink_health_reporter_create(bp->dl,
					       &bnxt_dl_fw_fatal_reporter_ops,
					       0, true, bp);
	if (IS_ERR(health->fw_fatal_reporter)) {
		netdev_warn(bp->dev, "Failed to create FW fatal health reporter, rc = %ld\n",
			    PTR_ERR(health->fw_fatal_reporter));
		health->fw_fatal_reporter = NULL;
	}
}