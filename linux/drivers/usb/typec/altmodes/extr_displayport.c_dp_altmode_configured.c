#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  conf; } ;
struct dp_altmode {TYPE_2__* alt; TYPE_3__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPEC_STATE_USB ; 
 int dp_altmode_notify (struct dp_altmode*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,char*,char*) ; 
 int typec_altmode_notify (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int dp_altmode_configured(struct dp_altmode *dp)
{
	int ret;

	sysfs_notify(&dp->alt->dev.kobj, "displayport", "configuration");

	if (!dp->data.conf)
		return typec_altmode_notify(dp->alt, TYPEC_STATE_USB,
					    &dp->data);

	ret = dp_altmode_notify(dp);
	if (ret)
		return ret;

	sysfs_notify(&dp->alt->dev.kobj, "displayport", "pin_assignment");

	return 0;
}