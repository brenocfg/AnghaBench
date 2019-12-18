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
struct rocker_port {struct rocker* rocker; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct rocker {TYPE_1__ hw; } ;
struct netdev_phys_item_id {int id_len; int /*<<< orphan*/  id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int rocker_port_get_port_parent_id(struct net_device *dev,
					  struct netdev_phys_item_id *ppid)
{
	const struct rocker_port *rocker_port = netdev_priv(dev);
	const struct rocker *rocker = rocker_port->rocker;

	ppid->id_len = sizeof(rocker->hw.id);
	memcpy(&ppid->id, &rocker->hw.id, ppid->id_len);

	return 0;
}