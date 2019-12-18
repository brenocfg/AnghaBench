#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct team_port {int dummy; } ;
struct team {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ap_opt_inst_info; struct team_port* active_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (struct team_port*,int /*<<< orphan*/ *) ; 
 TYPE_1__* ab_priv (struct team*) ; 
 int /*<<< orphan*/  team_option_inst_set_change (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab_port_leave(struct team *team, struct team_port *port)
{
	if (ab_priv(team)->active_port == port) {
		RCU_INIT_POINTER(ab_priv(team)->active_port, NULL);
		team_option_inst_set_change(ab_priv(team)->ap_opt_inst_info);
	}
}