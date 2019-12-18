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
struct myri10ge_priv {int /*<<< orphan*/  dev; } ;
struct myri10ge_cmd {int dummy; } ;

/* Variables and functions */
 int MXGEFW_DISABLE_PROMISC ; 
 int MXGEFW_ENABLE_PROMISC ; 
 int myri10ge_send_cmd (struct myri10ge_priv*,int,struct myri10ge_cmd*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
myri10ge_change_promisc(struct myri10ge_priv *mgp, int promisc, int atomic)
{
	struct myri10ge_cmd cmd;
	int status, ctl;

	ctl = promisc ? MXGEFW_ENABLE_PROMISC : MXGEFW_DISABLE_PROMISC;
	status = myri10ge_send_cmd(mgp, ctl, &cmd, atomic);
	if (status)
		netdev_err(mgp->dev, "Failed to set promisc mode\n");
}