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
struct TYPE_8__ {int /*<<< orphan*/  ecode; int /*<<< orphan*/  eid; } ;
struct TYPE_7__ {int /*<<< orphan*/  state; int /*<<< orphan*/  reset_code; } ;
union ionic_notifyq_comp {TYPE_4__ event; TYPE_3__ reset; } ;
typedef  scalar_t__ u64 ;
struct net_device {int dummy; } ;
struct ionic_queue {TYPE_1__* info; } ;
struct ionic_lif {scalar_t__ last_eid; TYPE_2__* ionic; struct net_device* netdev; } ;
struct ionic_cq_info {union ionic_notifyq_comp* cq_desc; } ;
struct ionic_cq {struct ionic_queue* bound_q; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct ionic_lif* cb_arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
#define  IONIC_EVENT_LINK_CHANGE 129 
#define  IONIC_EVENT_RESET 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dynamic_hex_dump (char*,int /*<<< orphan*/ ,int,int,union ionic_notifyq_comp*,int,int) ; 
 int /*<<< orphan*/  ionic_link_status_check_request (struct ionic_lif*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool ionic_notifyq_service(struct ionic_cq *cq,
				  struct ionic_cq_info *cq_info)
{
	union ionic_notifyq_comp *comp = cq_info->cq_desc;
	struct net_device *netdev;
	struct ionic_queue *q;
	struct ionic_lif *lif;
	u64 eid;

	q = cq->bound_q;
	lif = q->info[0].cb_arg;
	netdev = lif->netdev;
	eid = le64_to_cpu(comp->event.eid);

	/* Have we run out of new completions to process? */
	if (eid <= lif->last_eid)
		return false;

	lif->last_eid = eid;

	dev_dbg(lif->ionic->dev, "notifyq event:\n");
	dynamic_hex_dump("event ", DUMP_PREFIX_OFFSET, 16, 1,
			 comp, sizeof(*comp), true);

	switch (le16_to_cpu(comp->event.ecode)) {
	case IONIC_EVENT_LINK_CHANGE:
		ionic_link_status_check_request(lif);
		break;
	case IONIC_EVENT_RESET:
		netdev_info(netdev, "Notifyq IONIC_EVENT_RESET eid=%lld\n",
			    eid);
		netdev_info(netdev, "  reset_code=%d state=%d\n",
			    comp->reset.reset_code,
			    comp->reset.state);
		break;
	default:
		netdev_warn(netdev, "Notifyq unknown event ecode=%d eid=%lld\n",
			    comp->event.ecode, eid);
		break;
	}

	return true;
}