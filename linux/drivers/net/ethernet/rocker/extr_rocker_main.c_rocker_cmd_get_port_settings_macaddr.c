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

/* Variables and functions */
 int rocker_cmd_exec (struct rocker_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  rocker_cmd_get_port_settings_macaddr_proc ; 
 int /*<<< orphan*/  rocker_cmd_get_port_settings_prep ; 

__attribute__((used)) static int rocker_cmd_get_port_settings_macaddr(struct rocker_port *rocker_port,
						unsigned char *macaddr)
{
	return rocker_cmd_exec(rocker_port, false,
			       rocker_cmd_get_port_settings_prep, NULL,
			       rocker_cmd_get_port_settings_macaddr_proc,
			       macaddr);
}