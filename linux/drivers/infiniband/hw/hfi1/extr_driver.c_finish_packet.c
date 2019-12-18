#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hfi1_packet {int /*<<< orphan*/  numpkt; int /*<<< orphan*/  etail; int /*<<< orphan*/  updegr; TYPE_1__* rcd; } ;
struct TYPE_2__ {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcv_intr_dynamic ; 
 int /*<<< orphan*/  update_usrhead (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void finish_packet(struct hfi1_packet *packet)
{
	/*
	 * Nothing we need to free for the packet.
	 *
	 * The only thing we need to do is a final update and call for an
	 * interrupt
	 */
	update_usrhead(packet->rcd, packet->rcd->head, packet->updegr,
		       packet->etail, rcv_intr_dynamic, packet->numpkt);
}