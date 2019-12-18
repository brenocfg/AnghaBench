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
struct hfi1_packet {int /*<<< orphan*/  dlid; int /*<<< orphan*/  rhf; struct hfi1_ctxtdata* rcd; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_check_mcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_handle_packet (struct hfi1_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhf_dc_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_input_ibhdr (int /*<<< orphan*/ ,struct hfi1_packet*,int) ; 

void hfi1_ib_rcv(struct hfi1_packet *packet)
{
	struct hfi1_ctxtdata *rcd = packet->rcd;

	trace_input_ibhdr(rcd->dd, packet, !!(rhf_dc_info(packet->rhf)));
	hfi1_handle_packet(packet, hfi1_check_mcast(packet->dlid));
}