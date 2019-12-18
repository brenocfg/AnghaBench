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
struct switchdev_notifier_fdb_info {int offloaded; int /*<<< orphan*/  info; int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; } ;
struct rocker_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_FDB_OFFLOADED ; 
 int /*<<< orphan*/  call_switchdev_notifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rocker_fdb_offload_notify(struct rocker_port *rocker_port,
			  struct switchdev_notifier_fdb_info *recv_info)
{
	struct switchdev_notifier_fdb_info info;

	info.addr = recv_info->addr;
	info.vid = recv_info->vid;
	info.offloaded = true;
	call_switchdev_notifiers(SWITCHDEV_FDB_OFFLOADED,
				 rocker_port->dev, &info.info, NULL);
}