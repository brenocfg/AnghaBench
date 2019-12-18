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
struct rocker_port {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;
typedef  int /*<<< orphan*/  copy_ecmd ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ethtool_link_ksettings*,struct ethtool_link_ksettings const*,int) ; 
 int rocker_cmd_exec (struct rocker_port*,int,int /*<<< orphan*/ ,struct ethtool_link_ksettings*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_cmd_set_port_settings_ethtool_prep ; 

__attribute__((used)) static int
rocker_cmd_set_port_settings_ethtool(struct rocker_port *rocker_port,
				     const struct ethtool_link_ksettings *ecmd)
{
	struct ethtool_link_ksettings copy_ecmd;

	memcpy(&copy_ecmd, ecmd, sizeof(copy_ecmd));

	return rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_set_port_settings_ethtool_prep,
			       &copy_ecmd, NULL, NULL);
}