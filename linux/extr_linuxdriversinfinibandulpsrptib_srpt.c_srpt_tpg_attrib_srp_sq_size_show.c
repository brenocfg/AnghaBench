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
struct TYPE_2__ {int srp_sq_size; } ;
struct srpt_port {TYPE_1__ port_attrib; } ;
struct se_portal_group {int dummy; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct se_portal_group* attrib_to_tpg (struct config_item*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct srpt_port* srpt_tpg_to_sport (struct se_portal_group*) ; 

__attribute__((used)) static ssize_t srpt_tpg_attrib_srp_sq_size_show(struct config_item *item,
		char *page)
{
	struct se_portal_group *se_tpg = attrib_to_tpg(item);
	struct srpt_port *sport = srpt_tpg_to_sport(se_tpg);

	return sprintf(page, "%u\n", sport->port_attrib.srp_sq_size);
}