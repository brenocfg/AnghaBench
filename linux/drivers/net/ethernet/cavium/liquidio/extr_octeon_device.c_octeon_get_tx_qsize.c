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
typedef  size_t u32 ;
struct TYPE_3__ {int iq; } ;
struct octeon_device {TYPE_2__** instr_queue; TYPE_1__ io_qmask; } ;
struct TYPE_4__ {int max_count; } ;

/* Variables and functions */
 int BIT_ULL (size_t) ; 
 size_t MAX_OCTEON_INSTR_QUEUES (struct octeon_device*) ; 

int octeon_get_tx_qsize(struct octeon_device *oct, u32 q_no)

{
	if (oct && (q_no < MAX_OCTEON_INSTR_QUEUES(oct)) &&
	    (oct->io_qmask.iq & BIT_ULL(q_no)))
		return oct->instr_queue[q_no]->max_count;

	return -1;
}