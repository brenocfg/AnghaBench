#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct octeon_device {TYPE_1__* pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {struct lio* ctxptr; int /*<<< orphan*/  work; } ;
struct TYPE_6__ {TYPE_2__ wk; int /*<<< orphan*/  wq; } ;
struct lio {TYPE_3__ link_status_wq; struct octeon_device* oct_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  octnet_link_status_change ; 

__attribute__((used)) static inline int setup_link_status_change_wq(struct net_device *netdev)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;

	lio->link_status_wq.wq = alloc_workqueue("link-status",
						 WQ_MEM_RECLAIM, 0);
	if (!lio->link_status_wq.wq) {
		dev_err(&oct->pci_dev->dev, "unable to create cavium link status wq\n");
		return -1;
	}
	INIT_DELAYED_WORK(&lio->link_status_wq.wk.work,
			  octnet_link_status_change);
	lio->link_status_wq.wk.ctxptr = lio;

	return 0;
}