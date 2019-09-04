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
struct TYPE_3__ {int /*<<< orphan*/  ackid; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct ldc_packet {TYPE_2__ u; scalar_t__ seqid; scalar_t__ ctrl; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;
struct ldc_channel {scalar_t__ snd_nxt; int /*<<< orphan*/  rcv_nxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDC_ACK ; 
 int /*<<< orphan*/  LDC_DATA ; 
 struct ldc_packet* data_get_tx_packet (struct ldc_channel*,unsigned long*) ; 
 scalar_t__ likely (struct ldc_packet*) ; 
 int /*<<< orphan*/  memset (struct ldc_packet*,int /*<<< orphan*/ ,int) ; 
 int send_tx_packet (struct ldc_channel*,struct ldc_packet*,unsigned long) ; 

__attribute__((used)) static void send_data_ack(struct ldc_channel *lp)
{
	unsigned long new_tail;
	struct ldc_packet *p;

	p = data_get_tx_packet(lp, &new_tail);
	if (likely(p)) {
		int err;

		memset(p, 0, sizeof(*p));
		p->type = LDC_DATA;
		p->stype = LDC_ACK;
		p->ctrl = 0;
		p->seqid = lp->snd_nxt + 1;
		p->u.r.ackid = lp->rcv_nxt;

		err = send_tx_packet(lp, p, new_tail);
		if (!err)
			lp->snd_nxt++;
	}
}