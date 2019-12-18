#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {scalar_t__ id; } ;
struct TYPE_9__ {TYPE_1__ poll; } ;
struct xen_pvcalls_response {int req_id; scalar_t__ cmd; TYPE_2__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct sock_mapping {TYPE_3__ passive; } ;
struct TYPE_12__ {int /*<<< orphan*/  rsp_cons; } ;
struct pvcalls_bedata {int /*<<< orphan*/  inflight_req; TYPE_5__ ring; TYPE_4__* rsp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_11__ {int req_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PVCALLS_FLAG_POLL_INFLIGHT ; 
 int /*<<< orphan*/  PVCALLS_FLAG_POLL_RET ; 
 scalar_t__ PVCALLS_POLL ; 
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_RESPONSES (TYPE_5__*,int) ; 
 struct xen_pvcalls_response* RING_GET_RESPONSE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ RING_HAS_UNCONSUMED_RESPONSES (TYPE_5__*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,void*) ; 
 struct pvcalls_bedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvcalls_enter () ; 
 int /*<<< orphan*/  pvcalls_exit () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pvcalls_front_event_handler(int irq, void *dev_id)
{
	struct xenbus_device *dev = dev_id;
	struct pvcalls_bedata *bedata;
	struct xen_pvcalls_response *rsp;
	uint8_t *src, *dst;
	int req_id = 0, more = 0, done = 0;

	if (dev == NULL)
		return IRQ_HANDLED;

	pvcalls_enter();
	bedata = dev_get_drvdata(&dev->dev);
	if (bedata == NULL) {
		pvcalls_exit();
		return IRQ_HANDLED;
	}

again:
	while (RING_HAS_UNCONSUMED_RESPONSES(&bedata->ring)) {
		rsp = RING_GET_RESPONSE(&bedata->ring, bedata->ring.rsp_cons);

		req_id = rsp->req_id;
		if (rsp->cmd == PVCALLS_POLL) {
			struct sock_mapping *map = (struct sock_mapping *)(uintptr_t)
						   rsp->u.poll.id;

			clear_bit(PVCALLS_FLAG_POLL_INFLIGHT,
				  (void *)&map->passive.flags);
			/*
			 * clear INFLIGHT, then set RET. It pairs with
			 * the checks at the beginning of
			 * pvcalls_front_poll_passive.
			 */
			smp_wmb();
			set_bit(PVCALLS_FLAG_POLL_RET,
				(void *)&map->passive.flags);
		} else {
			dst = (uint8_t *)&bedata->rsp[req_id] +
			      sizeof(rsp->req_id);
			src = (uint8_t *)rsp + sizeof(rsp->req_id);
			memcpy(dst, src, sizeof(*rsp) - sizeof(rsp->req_id));
			/*
			 * First copy the rest of the data, then req_id. It is
			 * paired with the barrier when accessing bedata->rsp.
			 */
			smp_wmb();
			bedata->rsp[req_id].req_id = req_id;
		}

		done = 1;
		bedata->ring.rsp_cons++;
	}

	RING_FINAL_CHECK_FOR_RESPONSES(&bedata->ring, more);
	if (more)
		goto again;
	if (done)
		wake_up(&bedata->inflight_req);
	pvcalls_exit();
	return IRQ_HANDLED;
}