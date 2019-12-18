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
struct team_option_inst_info {struct team_port* port; } ;
struct team {int dummy; } ;
struct TYPE_2__ {struct team_option_inst_info* opt_inst_info; } ;
struct lb_port_priv {TYPE_1__ stats_info; } ;

/* Variables and functions */
 struct lb_port_priv* get_lb_port_priv (struct team_port*) ; 

__attribute__((used)) static int lb_port_stats_init(struct team *team,
			      struct team_option_inst_info *info)
{
	struct team_port *port = info->port;
	struct lb_port_priv *lb_port_priv = get_lb_port_priv(port);

	lb_port_priv->stats_info.opt_inst_info = info;
	return 0;
}