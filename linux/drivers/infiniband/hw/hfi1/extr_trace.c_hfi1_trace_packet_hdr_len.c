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
typedef  int /*<<< orphan*/  u8 ;
struct hfi1_packet {scalar_t__ etype; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 scalar_t__ RHF_RCV_TYPE_BYPASS ; 
 int /*<<< orphan*/  __get_16b_hdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_ib_hdr_len (int /*<<< orphan*/ ) ; 

u8 hfi1_trace_packet_hdr_len(struct hfi1_packet *packet)
{
	if (packet->etype != RHF_RCV_TYPE_BYPASS)
		return __get_ib_hdr_len(packet->hdr);
	else
		return __get_16b_hdr_len(packet->hdr);
}