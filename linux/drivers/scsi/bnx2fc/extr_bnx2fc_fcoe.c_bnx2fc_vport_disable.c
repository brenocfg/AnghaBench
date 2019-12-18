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
struct fc_vport {struct fc_lport* dd_data; } ;
struct fc_lport {int /*<<< orphan*/  boot_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_DISABLED ; 
 int /*<<< orphan*/  fc_fabric_login (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_fabric_logoff (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_vport_set_state (struct fc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_vport_setlink (struct fc_lport*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static int bnx2fc_vport_disable(struct fc_vport *vport, bool disable)
{
	struct fc_lport *lport = vport->dd_data;

	if (disable) {
		fc_vport_set_state(vport, FC_VPORT_DISABLED);
		fc_fabric_logoff(lport);
	} else {
		lport->boot_time = jiffies;
		fc_fabric_login(lport);
		fc_vport_setlink(lport);
	}
	return 0;
}