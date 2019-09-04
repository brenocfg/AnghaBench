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
struct rxe_pkt_info {size_t paylen; size_t opcode; } ;
struct TYPE_2__ {size_t* offset; } ;

/* Variables and functions */
 size_t RXE_ICRC_SIZE ; 
 size_t RXE_PAYLOAD ; 
 size_t bth_pad (struct rxe_pkt_info*) ; 
 TYPE_1__* rxe_opcode ; 

__attribute__((used)) static inline size_t payload_size(struct rxe_pkt_info *pkt)
{
	return pkt->paylen - rxe_opcode[pkt->opcode].offset[RXE_PAYLOAD]
		- bth_pad(pkt) - RXE_ICRC_SIZE;
}