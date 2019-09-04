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
struct TYPE_5__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct TYPE_6__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
union blkif_back_rings {TYPE_2__ common; TYPE_3__ x86_64; TYPE_3__ x86_32; TYPE_3__ native; } ;
typedef  int /*<<< orphan*/  u64 ;
struct xen_blkif_ring {int /*<<< orphan*/  irq; int /*<<< orphan*/  blk_ring_lock; TYPE_1__* blkif; union blkif_back_rings blk_rings; } ;
struct blkif_response {unsigned short operation; int status; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int blk_protocol; } ;

/* Variables and functions */
#define  BLKIF_PROTOCOL_NATIVE 130 
#define  BLKIF_PROTOCOL_X86_32 129 
#define  BLKIF_PROTOCOL_X86_64 128 
 int /*<<< orphan*/  BUG () ; 
 struct blkif_response* RING_GET_RESPONSE (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_PUSH_RESPONSES_AND_CHECK_NOTIFY (TYPE_2__*,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void make_response(struct xen_blkif_ring *ring, u64 id,
			  unsigned short op, int st)
{
	struct blkif_response *resp;
	unsigned long     flags;
	union blkif_back_rings *blk_rings;
	int notify;

	spin_lock_irqsave(&ring->blk_ring_lock, flags);
	blk_rings = &ring->blk_rings;
	/* Place on the response ring for the relevant domain. */
	switch (ring->blkif->blk_protocol) {
	case BLKIF_PROTOCOL_NATIVE:
		resp = RING_GET_RESPONSE(&blk_rings->native,
					 blk_rings->native.rsp_prod_pvt);
		break;
	case BLKIF_PROTOCOL_X86_32:
		resp = RING_GET_RESPONSE(&blk_rings->x86_32,
					 blk_rings->x86_32.rsp_prod_pvt);
		break;
	case BLKIF_PROTOCOL_X86_64:
		resp = RING_GET_RESPONSE(&blk_rings->x86_64,
					 blk_rings->x86_64.rsp_prod_pvt);
		break;
	default:
		BUG();
	}

	resp->id        = id;
	resp->operation = op;
	resp->status    = st;

	blk_rings->common.rsp_prod_pvt++;
	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&blk_rings->common, notify);
	spin_unlock_irqrestore(&ring->blk_ring_lock, flags);
	if (notify)
		notify_remote_via_irq(ring->irq);
}