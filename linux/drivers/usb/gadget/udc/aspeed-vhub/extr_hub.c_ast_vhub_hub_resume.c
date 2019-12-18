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
struct ast_vhub_port {int status; int /*<<< orphan*/  dev; } ;
struct ast_vhub {int suspended; struct ast_vhub_port* ports; } ;

/* Variables and functions */
 unsigned int AST_VHUB_NUM_PORTS ; 
 int /*<<< orphan*/  UDCDBG (struct ast_vhub*,char*) ; 
 int USB_PORT_STAT_SUSPEND ; 
 int /*<<< orphan*/  ast_vhub_dev_resume (int /*<<< orphan*/ *) ; 

void ast_vhub_hub_resume(struct ast_vhub *vhub)
{
	unsigned int i;

	UDCDBG(vhub, "USB bus resume\n");

	if (!vhub->suspended)
		return;

	vhub->suspended = false;

	/*
	 * Forward to unsuspended ports without changing
	 * their connection status.
	 */
	for (i = 0; i < AST_VHUB_NUM_PORTS; i++) {
		struct ast_vhub_port *p = &vhub->ports[i];

		if (!(p->status & USB_PORT_STAT_SUSPEND))
			ast_vhub_dev_resume(&p->dev);
	}
}