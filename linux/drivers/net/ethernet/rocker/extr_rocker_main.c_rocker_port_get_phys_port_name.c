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
struct port_name {char* buf; size_t len; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int rocker_cmd_exec (struct rocker_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct port_name*) ; 
 int /*<<< orphan*/  rocker_cmd_get_port_settings_phys_name_proc ; 
 int /*<<< orphan*/  rocker_cmd_get_port_settings_prep ; 

__attribute__((used)) static int rocker_port_get_phys_port_name(struct net_device *dev,
					  char *buf, size_t len)
{
	struct rocker_port *rocker_port = netdev_priv(dev);
	struct port_name name = { .buf = buf, .len = len };
	int err;

	err = rocker_cmd_exec(rocker_port, false,
			      rocker_cmd_get_port_settings_prep, NULL,
			      rocker_cmd_get_port_settings_phys_name_proc,
			      &name);

	return err ? -EOPNOTSUPP : 0;
}