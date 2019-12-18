#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rdma_ah_attr {int /*<<< orphan*/  type; } ;
struct mthca_dev {int /*<<< orphan*/  sm_lock; struct ib_ah** sm_ah; TYPE_2__*** send_agent; int /*<<< orphan*/  ib_dev; } ;
struct ib_ah {int dummy; } ;
struct TYPE_4__ {TYPE_1__* qp; } ;
struct TYPE_3__ {int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_ah*) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_find_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int) ; 
 struct ib_ah* rdma_create_ah (int /*<<< orphan*/ ,struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_ah (struct ib_ah*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void update_sm_ah(struct mthca_dev *dev,
			 u8 port_num, u16 lid, u8 sl)
{
	struct ib_ah *new_ah;
	struct rdma_ah_attr ah_attr;
	unsigned long flags;

	if (!dev->send_agent[port_num - 1][0])
		return;

	memset(&ah_attr, 0, sizeof ah_attr);
	ah_attr.type = rdma_ah_find_type(&dev->ib_dev, port_num);
	rdma_ah_set_dlid(&ah_attr, lid);
	rdma_ah_set_sl(&ah_attr, sl);
	rdma_ah_set_port_num(&ah_attr, port_num);

	new_ah = rdma_create_ah(dev->send_agent[port_num - 1][0]->qp->pd,
				&ah_attr, 0);
	if (IS_ERR(new_ah))
		return;

	spin_lock_irqsave(&dev->sm_lock, flags);
	if (dev->sm_ah[port_num - 1])
		rdma_destroy_ah(dev->sm_ah[port_num - 1], 0);
	dev->sm_ah[port_num - 1] = new_ah;
	spin_unlock_irqrestore(&dev->sm_lock, flags);
}