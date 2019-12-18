#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ucsi_control {int dummy; } ;
struct ucsi_connector {TYPE_1__* ucsi; } ;
struct TYPE_3__ {int /*<<< orphan*/  ppm_lock; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  UCSI_CMD_SET_NTFY_ENABLE (struct ucsi_control,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCSI_ENABLE_NTFY_ALL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucsi_reset_connector (struct ucsi_connector*,int) ; 
 int /*<<< orphan*/  ucsi_reset_ppm (TYPE_1__*) ; 
 int ucsi_send_command (TYPE_1__*,struct ucsi_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_role_cmd(struct ucsi_connector *con, struct ucsi_control *ctrl)
{
	int ret;

	ret = ucsi_send_command(con->ucsi, ctrl, NULL, 0);
	if (ret == -ETIMEDOUT) {
		struct ucsi_control c;

		/* PPM most likely stopped responding. Resetting everything. */
		mutex_lock(&con->ucsi->ppm_lock);
		ucsi_reset_ppm(con->ucsi);
		mutex_unlock(&con->ucsi->ppm_lock);

		UCSI_CMD_SET_NTFY_ENABLE(c, UCSI_ENABLE_NTFY_ALL);
		ucsi_send_command(con->ucsi, &c, NULL, 0);

		ucsi_reset_connector(con, true);
	}

	return ret;
}