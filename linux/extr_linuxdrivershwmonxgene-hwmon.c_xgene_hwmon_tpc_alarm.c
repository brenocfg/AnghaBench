#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xgene_hwmon_dev {int temp_critical_alarm; TYPE_1__* dev; } ;
struct slimpro_resp_msg {int /*<<< orphan*/  param2; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int xgene_hwmon_tpc_alarm(struct xgene_hwmon_dev *ctx,
				 struct slimpro_resp_msg *amsg)
{
	ctx->temp_critical_alarm = !!amsg->param2;
	sysfs_notify(&ctx->dev->kobj, NULL, "temp1_critical_alarm");

	return 0;
}