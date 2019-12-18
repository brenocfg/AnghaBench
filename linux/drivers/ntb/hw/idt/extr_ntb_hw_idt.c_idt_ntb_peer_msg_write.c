#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ntb_dev {int dummy; } ;
struct idt_ntb_dev {int peer_cnt; size_t part; int /*<<< orphan*/ * msg_locks; TYPE_1__* peers; } ;
struct TYPE_8__ {TYPE_2__* msgs; } ;
struct TYPE_7__ {int /*<<< orphan*/ * msgctl; } ;
struct TYPE_6__ {int /*<<< orphan*/  out; } ;
struct TYPE_5__ {int part; } ;

/* Variables and functions */
 int EINVAL ; 
 int IDT_MSG_CNT ; 
 int SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SWPxMSGCTL_PART ; 
 int /*<<< orphan*/  SWPxMSGCTL_REG ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idt_sw_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ ntdata_tbl ; 
 TYPE_3__* partdata_tbl ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static int idt_ntb_peer_msg_write(struct ntb_dev *ntb, int pidx, int midx,
				  u32 msg)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	unsigned long irqflags;
	u32 swpmsgctl = 0;

	if (midx < 0 || IDT_MSG_CNT <= midx)
		return -EINVAL;

	if (pidx < 0 || ndev->peer_cnt <= pidx)
		return -EINVAL;

	/* Collect the routing information */
	swpmsgctl = SET_FIELD(SWPxMSGCTL_REG, 0, midx) |
		    SET_FIELD(SWPxMSGCTL_PART, 0, ndev->peers[pidx].part);

	/* Lock the messages routing table of the specified register */
	spin_lock_irqsave(&ndev->msg_locks[midx], irqflags);
	/* Set the route and send the data */
	idt_sw_write(ndev, partdata_tbl[ndev->part].msgctl[midx], swpmsgctl);
	idt_nt_write(ndev, ntdata_tbl.msgs[midx].out, msg);
	/* Unlock the messages routing table */
	spin_unlock_irqrestore(&ndev->msg_locks[midx], irqflags);

	/* Client driver shall check the status register */
	return 0;
}