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
struct srpt_port {int enabled; } ;
struct se_portal_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_tpg_deregister (struct se_portal_group*) ; 
 struct srpt_port* srpt_tpg_to_sport (struct se_portal_group*) ; 

__attribute__((used)) static void srpt_drop_tpg(struct se_portal_group *tpg)
{
	struct srpt_port *sport = srpt_tpg_to_sport(tpg);

	sport->enabled = false;
	core_tpg_deregister(tpg);
}