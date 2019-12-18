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
struct hfi1_packet {int /*<<< orphan*/  rhf; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  ppd; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcv_hdrerr (struct hfi1_ctxtdata*,int /*<<< orphan*/ ,struct hfi1_packet*) ; 
 scalar_t__ rhf_err_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_eflags_errs (struct hfi1_packet*) ; 

void handle_eflags(struct hfi1_packet *packet)
{
	struct hfi1_ctxtdata *rcd = packet->rcd;

	rcv_hdrerr(rcd, rcd->ppd, packet);
	if (rhf_err_flags(packet->rhf))
		show_eflags_errs(packet);
}