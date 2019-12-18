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
struct ucsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCSI_CMD_SET_NTFY_ENABLE (struct ucsi_control,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UCSI_ENABLE_NTFY_ALL ; 
 int ucsi_send_command (struct ucsi*,struct ucsi_control*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ucsi_resume(struct ucsi *ucsi)
{
	struct ucsi_control ctrl;

	/* Restore UCSI notification enable mask after system resume */
	UCSI_CMD_SET_NTFY_ENABLE(ctrl, UCSI_ENABLE_NTFY_ALL);
	return ucsi_send_command(ucsi, &ctrl, NULL, 0);
}