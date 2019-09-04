#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netdev_event_work_cmd {int dummy; } ;
struct netdev_event_work {int /*<<< orphan*/  work; TYPE_1__* cmds; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct net_device* filter_ndev; struct net_device* ndev; scalar_t__ cb; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  gid_cache_wq ; 
 struct netdev_event_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct netdev_event_work_cmd*,int) ; 
 int /*<<< orphan*/  netdevice_event_work_handler ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdevice_queue_work(struct netdev_event_work_cmd *cmds,
				struct net_device *ndev)
{
	unsigned int i;
	struct netdev_event_work *ndev_work =
		kmalloc(sizeof(*ndev_work), GFP_KERNEL);

	if (!ndev_work)
		return NOTIFY_DONE;

	memcpy(ndev_work->cmds, cmds, sizeof(ndev_work->cmds));
	for (i = 0; i < ARRAY_SIZE(ndev_work->cmds) && ndev_work->cmds[i].cb; i++) {
		if (!ndev_work->cmds[i].ndev)
			ndev_work->cmds[i].ndev = ndev;
		if (!ndev_work->cmds[i].filter_ndev)
			ndev_work->cmds[i].filter_ndev = ndev;
		dev_hold(ndev_work->cmds[i].ndev);
		dev_hold(ndev_work->cmds[i].filter_ndev);
	}
	INIT_WORK(&ndev_work->work, netdevice_event_work_handler);

	queue_work(gid_cache_wq, &ndev_work->work);

	return NOTIFY_DONE;
}