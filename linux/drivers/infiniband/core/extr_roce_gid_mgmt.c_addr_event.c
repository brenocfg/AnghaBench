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
struct TYPE_2__ {struct net_device* ndev; } ;
struct update_gid_event_work {int gid_op; int /*<<< orphan*/  work; TYPE_1__ gid_attr; int /*<<< orphan*/  gid; } ;
struct sockaddr {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ type; } ;
typedef  enum gid_op_type { ____Placeholder_gid_op_type } gid_op_type ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int GID_ADD ; 
 int GID_DEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NETDEV_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  gid_cache_wq ; 
 struct update_gid_event_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ip2gid (struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_gid_event_work_handler ; 

__attribute__((used)) static int addr_event(struct notifier_block *this, unsigned long event,
		      struct sockaddr *sa, struct net_device *ndev)
{
	struct update_gid_event_work *work;
	enum gid_op_type gid_op;

	if (ndev->type != ARPHRD_ETHER)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		gid_op = GID_ADD;
		break;

	case NETDEV_DOWN:
		gid_op = GID_DEL;
		break;

	default:
		return NOTIFY_DONE;
	}

	work = kmalloc(sizeof(*work), GFP_ATOMIC);
	if (!work)
		return NOTIFY_DONE;

	INIT_WORK(&work->work, update_gid_event_work_handler);

	rdma_ip2gid(sa, &work->gid);
	work->gid_op = gid_op;

	memset(&work->gid_attr, 0, sizeof(work->gid_attr));
	dev_hold(ndev);
	work->gid_attr.ndev   = ndev;

	queue_work(gid_cache_wq, &work->work);

	return NOTIFY_DONE;
}