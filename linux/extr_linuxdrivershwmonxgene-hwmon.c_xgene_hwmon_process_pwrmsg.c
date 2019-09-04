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
struct xgene_hwmon_dev {int dummy; } ;
struct slimpro_resp_msg {int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 scalar_t__ MSG_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ PWRMGMT_SUBTYPE_TPC ; 
 scalar_t__ TPC_ALARM ; 
 scalar_t__ TPC_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_hwmon_tpc_alarm (struct xgene_hwmon_dev*,struct slimpro_resp_msg*) ; 

__attribute__((used)) static void xgene_hwmon_process_pwrmsg(struct xgene_hwmon_dev *ctx,
				       struct slimpro_resp_msg *amsg)
{
	if ((MSG_SUBTYPE(amsg->msg) == PWRMGMT_SUBTYPE_TPC) &&
	    (TPC_CMD(amsg->msg) == TPC_ALARM))
		xgene_hwmon_tpc_alarm(ctx, amsg);
}