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
struct hfi1_packet {int numpkt; } ;

/* Variables and functions */
 int MAX_PKT_RECV ; 
 int RCV_PKT_OK ; 
 int max_packet_exceeded (struct hfi1_packet*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int check_max_packet(struct hfi1_packet *packet, int thread)
{
	int ret = RCV_PKT_OK;

	if (unlikely((packet->numpkt & (MAX_PKT_RECV - 1)) == 0))
		ret = max_packet_exceeded(packet, thread);
	return ret;
}