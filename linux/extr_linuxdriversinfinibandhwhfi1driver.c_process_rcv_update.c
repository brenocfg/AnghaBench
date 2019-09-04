#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hfi1_packet {int numpkt; int /*<<< orphan*/ * grh; scalar_t__ updegr; int /*<<< orphan*/  etail; int /*<<< orphan*/  rhqoff; int /*<<< orphan*/  rcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  update_usrhead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void process_rcv_update(int last, struct hfi1_packet *packet)
{
	/*
	 * Update head regs etc., every 16 packets, if not last pkt,
	 * to help prevent rcvhdrq overflows, when many packets
	 * are processed and queue is nearly full.
	 * Don't request an interrupt for intermediate updates.
	 */
	if (!last && !(packet->numpkt & 0xf)) {
		update_usrhead(packet->rcd, packet->rhqoff, packet->updegr,
			       packet->etail, 0, 0);
		packet->updegr = 0;
	}
	packet->grh = NULL;
}