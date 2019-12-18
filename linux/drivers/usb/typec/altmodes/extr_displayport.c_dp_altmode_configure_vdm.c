#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  conf; } ;
struct dp_altmode {TYPE_3__ data; TYPE_1__* alt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_CMD_CONFIGURE ; 
 scalar_t__ DP_CONF_GET_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_HEADER (struct dp_altmode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEC_STATE_SAFE ; 
 int /*<<< orphan*/  TYPEC_STATE_USB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dp_altmode_notify (struct dp_altmode*) ; 
 int typec_altmode_notify (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int typec_altmode_vdm (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dp_altmode_configure_vdm(struct dp_altmode *dp, u32 conf)
{
	u32 header = DP_HEADER(dp, DP_CMD_CONFIGURE);
	int ret;

	ret = typec_altmode_notify(dp->alt, TYPEC_STATE_SAFE, &dp->data);
	if (ret) {
		dev_err(&dp->alt->dev,
			"unable to put to connector to safe mode\n");
		return ret;
	}

	ret = typec_altmode_vdm(dp->alt, header, &conf, 2);
	if (ret) {
		if (DP_CONF_GET_PIN_ASSIGN(dp->data.conf))
			dp_altmode_notify(dp);
		else
			typec_altmode_notify(dp->alt, TYPEC_STATE_USB,
					     &dp->data);
	}

	return ret;
}