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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct nozomi {TYPE_2__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {scalar_t__ update_flow_control; int /*<<< orphan*/ * ul_addr; TYPE_1__ ctrl_ul; } ;

/* Variables and functions */
 size_t MAX_PORT ; 
 size_t PORT_CTRL ; 
 size_t PORT_MDM ; 
 int /*<<< orphan*/  port2ctrl (size_t,struct nozomi*) ; 
 int /*<<< orphan*/  write_mem32 (int /*<<< orphan*/ ,size_t*,int) ; 

__attribute__((used)) static int send_flow_control(struct nozomi *dc)
{
	u32 i, more_flow_control_to_be_updated = 0;
	u16 *ctrl;

	for (i = PORT_MDM; i < MAX_PORT; i++) {
		if (dc->port[i].update_flow_control) {
			if (more_flow_control_to_be_updated) {
				/* We have more flow control to be updated */
				return 1;
			}
			dc->port[i].ctrl_ul.port = port2ctrl(i, dc);
			ctrl = (u16 *)&dc->port[i].ctrl_ul;
			write_mem32(dc->port[PORT_CTRL].ul_addr[0], \
				(u32 *) ctrl, 2);
			dc->port[i].update_flow_control = 0;
			more_flow_control_to_be_updated = 1;
		}
	}
	return 0;
}