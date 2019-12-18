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
struct ucsi_control {int dummy; } ;
struct ucsi_connector {int /*<<< orphan*/  ucsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCSI_CMD_CONNECTOR_RESET (struct ucsi_control,struct ucsi_connector*,int) ; 
 int ucsi_send_command (int /*<<< orphan*/ ,struct ucsi_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucsi_reset_connector(struct ucsi_connector *con, bool hard)
{
	struct ucsi_control ctrl;

	UCSI_CMD_CONNECTOR_RESET(ctrl, con, hard);

	return ucsi_send_command(con->ucsi, &ctrl, NULL, 0);
}