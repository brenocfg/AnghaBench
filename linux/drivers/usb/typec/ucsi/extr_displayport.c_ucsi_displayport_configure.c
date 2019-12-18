#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  conf; } ;
struct ucsi_dp {TYPE_2__* con; int /*<<< orphan*/  offset; int /*<<< orphan*/  override; TYPE_1__ data; } ;
struct ucsi_control {int /*<<< orphan*/  raw_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucsi; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_CONF_GET_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCSI_CMD_SET_NEW_CAM (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ucsi_send_command (int /*<<< orphan*/ ,struct ucsi_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_displayport_configure(struct ucsi_dp *dp)
{
	u32 pins = DP_CONF_GET_PIN_ASSIGN(dp->data.conf);
	struct ucsi_control ctrl;

	if (!dp->override)
		return 0;

	ctrl.raw_cmd = UCSI_CMD_SET_NEW_CAM(dp->con->num, 1, dp->offset, pins);

	return ucsi_send_command(dp->con->ucsi, &ctrl, NULL, 0);
}