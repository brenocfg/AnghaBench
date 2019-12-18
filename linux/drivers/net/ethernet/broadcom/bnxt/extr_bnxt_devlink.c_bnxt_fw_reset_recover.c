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
struct devlink_health_reporter {int dummy; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  bnxt_fw_reset (struct bnxt*) ; 
 struct bnxt* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 

__attribute__((used)) static int bnxt_fw_reset_recover(struct devlink_health_reporter *reporter,
				 void *priv_ctx)
{
	struct bnxt *bp = devlink_health_reporter_priv(reporter);

	if (!priv_ctx)
		return -EOPNOTSUPP;

	bnxt_fw_reset(bp);
	return 0;
}