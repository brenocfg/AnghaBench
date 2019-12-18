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
struct bfa_cee_lldp_cfg {void* enabled_system_cap; void* time_to_live; } ;

/* Variables and functions */
 void* ntohs (void*) ; 

__attribute__((used)) static void
bfa_cee_format_lldp_cfg(struct bfa_cee_lldp_cfg *lldp_cfg)
{
	lldp_cfg->time_to_live =
			ntohs(lldp_cfg->time_to_live);
	lldp_cfg->enabled_system_cap =
			ntohs(lldp_cfg->enabled_system_cap);
}