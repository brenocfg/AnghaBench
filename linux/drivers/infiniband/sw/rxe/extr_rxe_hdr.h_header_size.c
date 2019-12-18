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
struct rxe_pkt_info {size_t offset; size_t opcode; } ;
struct TYPE_2__ {size_t length; } ;

/* Variables and functions */
 TYPE_1__* rxe_opcode ; 

__attribute__((used)) static inline size_t header_size(struct rxe_pkt_info *pkt)
{
	return pkt->offset + rxe_opcode[pkt->opcode].length;
}