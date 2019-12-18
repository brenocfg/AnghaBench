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
struct se_portal_group {int dummy; } ;
struct srpt_port {char* port_guid; char* port_gid; struct se_portal_group port_guid_tpg; struct se_portal_group port_gid_tpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct srpt_port* srpt_tpg_to_sport (struct se_portal_group*) ; 

__attribute__((used)) static char *srpt_get_fabric_wwn(struct se_portal_group *tpg)
{
	struct srpt_port *sport = srpt_tpg_to_sport(tpg);

	WARN_ON_ONCE(tpg != &sport->port_guid_tpg &&
		     tpg != &sport->port_gid_tpg);
	return tpg == &sport->port_guid_tpg ? sport->port_guid :
		sport->port_gid;
}