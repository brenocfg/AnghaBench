#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct octeon_device {int ifcount; int num_oqs; TYPE_5__* pci_dev; TYPE_1__* props; int /*<<< orphan*/  cmd_resp_wqlock; int /*<<< orphan*/  cmd_resp_state; } ;
struct TYPE_9__ {TYPE_3__* rxpciq; } ;
struct lio {TYPE_4__ linfo; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_8__ {TYPE_2__ s; } ;
struct TYPE_6__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 struct lio* GET_LIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCT_DRV_OFFLINE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  liquidio_destroy_nic_device (struct octeon_device*,int) ; 
 int /*<<< orphan*/  octeon_unregister_droq_ops (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int liquidio_stop_nic_module(struct octeon_device *oct)
{
	struct lio *lio;
	int i, j;

	dev_dbg(&oct->pci_dev->dev, "Stopping network interfaces\n");
	if (!oct->ifcount) {
		dev_err(&oct->pci_dev->dev, "Init for Octeon was not completed\n");
		return 1;
	}

	spin_lock_bh(&oct->cmd_resp_wqlock);
	oct->cmd_resp_state = OCT_DRV_OFFLINE;
	spin_unlock_bh(&oct->cmd_resp_wqlock);

	for (i = 0; i < oct->ifcount; i++) {
		lio = GET_LIO(oct->props[i].netdev);
		for (j = 0; j < oct->num_oqs; j++)
			octeon_unregister_droq_ops(oct,
						   lio->linfo.rxpciq[j].s.q_no);
	}

	for (i = 0; i < oct->ifcount; i++)
		liquidio_destroy_nic_device(oct, i);

	dev_dbg(&oct->pci_dev->dev, "Network interfaces stopped\n");
	return 0;
}