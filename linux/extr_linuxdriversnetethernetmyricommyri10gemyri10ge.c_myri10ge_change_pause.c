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
struct myri10ge_priv {int pause; int /*<<< orphan*/  dev; } ;
struct myri10ge_cmd {int dummy; } ;

/* Variables and functions */
 int MXGEFW_DISABLE_FLOW_CONTROL ; 
 int MXGEFW_ENABLE_FLOW_CONTROL ; 
 int myri10ge_send_cmd (struct myri10ge_priv*,int,struct myri10ge_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int myri10ge_change_pause(struct myri10ge_priv *mgp, int pause)
{
	struct myri10ge_cmd cmd;
	int status, ctl;

	ctl = pause ? MXGEFW_ENABLE_FLOW_CONTROL : MXGEFW_DISABLE_FLOW_CONTROL;
	status = myri10ge_send_cmd(mgp, ctl, &cmd, 0);

	if (status) {
		netdev_err(mgp->dev, "Failed to set flow control mode\n");
		return status;
	}
	mgp->pause = pause;
	return 0;
}