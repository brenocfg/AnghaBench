#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
union oct_link_status {scalar_t__ u64; } ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct net_device {int max_mtu; scalar_t__ mtu; } ;
struct TYPE_11__ {int /*<<< orphan*/  work; } ;
struct TYPE_12__ {TYPE_5__ wk; int /*<<< orphan*/  wq; } ;
struct TYPE_8__ {int mtu; scalar_t__ link_up; } ;
struct TYPE_9__ {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_10__ {TYPE_3__ link; } ;
struct lio {TYPE_6__ link_status_wq; TYPE_4__ linfo; int /*<<< orphan*/  link_changes; scalar_t__ intf_open; struct octeon_device* oct_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  print_link_info (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_txqs (struct net_device*) ; 
 int /*<<< orphan*/  wake_txqs (struct net_device*) ; 

__attribute__((used)) static void update_link_status(struct net_device *netdev,
			       union oct_link_status *ls)
{
	struct lio *lio = GET_LIO(netdev);
	int current_max_mtu = lio->linfo.link.s.mtu;
	struct octeon_device *oct = lio->oct_dev;

	if ((lio->intf_open) && (lio->linfo.link.u64 != ls->u64)) {
		lio->linfo.link.u64 = ls->u64;

		print_link_info(netdev);
		lio->link_changes++;

		if (lio->linfo.link.s.link_up) {
			netif_carrier_on(netdev);
			wake_txqs(netdev);
		} else {
			netif_carrier_off(netdev);
			stop_txqs(netdev);
		}

		if (lio->linfo.link.s.mtu != current_max_mtu) {
			dev_info(&oct->pci_dev->dev,
				 "Max MTU Changed from %d to %d\n",
				 current_max_mtu, lio->linfo.link.s.mtu);
			netdev->max_mtu = lio->linfo.link.s.mtu;
		}

		if (lio->linfo.link.s.mtu < netdev->mtu) {
			dev_warn(&oct->pci_dev->dev,
				 "Current MTU is higher than new max MTU; Reducing the current mtu from %d to %d\n",
				 netdev->mtu, lio->linfo.link.s.mtu);
			queue_delayed_work(lio->link_status_wq.wq,
					   &lio->link_status_wq.wk.work, 0);
		}
	}
}