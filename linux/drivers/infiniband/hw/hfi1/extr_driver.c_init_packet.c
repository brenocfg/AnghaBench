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
struct hfi1_packet {int rsize; int maxcnt; int etail; scalar_t__ numpkt; int /*<<< orphan*/  rhqoff; int /*<<< orphan*/  rhf_addr; int /*<<< orphan*/  rhf; scalar_t__ updegr; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_ctxtdata {int rcvhdrqentsize; int rcvhdrq_cnt; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_rhf_addr (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  rhf_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void init_packet(struct hfi1_ctxtdata *rcd,
			       struct hfi1_packet *packet)
{
	packet->rsize = rcd->rcvhdrqentsize; /* words */
	packet->maxcnt = rcd->rcvhdrq_cnt * packet->rsize; /* words */
	packet->rcd = rcd;
	packet->updegr = 0;
	packet->etail = -1;
	packet->rhf_addr = get_rhf_addr(rcd);
	packet->rhf = rhf_to_cpu(packet->rhf_addr);
	packet->rhqoff = rcd->head;
	packet->numpkt = 0;
}