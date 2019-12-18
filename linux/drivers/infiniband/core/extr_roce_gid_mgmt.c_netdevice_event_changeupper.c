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
struct netdev_notifier_changeupper_info {scalar_t__ linking; } ;
struct netdev_event_work_cmd {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndev_event_link (struct net_device*,struct netdev_notifier_changeupper_info*,struct netdev_event_work_cmd*) ; 
 int /*<<< orphan*/  ndev_event_unlink (struct netdev_notifier_changeupper_info*,struct netdev_event_work_cmd*) ; 

__attribute__((used)) static void netdevice_event_changeupper(struct net_device *event_ndev,
		struct netdev_notifier_changeupper_info *changeupper_info,
		struct netdev_event_work_cmd *cmds)
{
	if (changeupper_info->linking)
		ndev_event_link(event_ndev, changeupper_info, cmds);
	else
		ndev_event_unlink(changeupper_info, cmds);
}