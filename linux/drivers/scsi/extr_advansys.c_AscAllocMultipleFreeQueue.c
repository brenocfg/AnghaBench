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
typedef  scalar_t__ uchar ;
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 scalar_t__ ASC_QLINK_END ; 
 scalar_t__ AscAllocFreeQueue (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uchar
AscAllocMultipleFreeQueue(PortAddr iop_base, uchar free_q_head, uchar n_free_q)
{
	uchar i;

	for (i = 0; i < n_free_q; i++) {
		free_q_head = AscAllocFreeQueue(iop_base, free_q_head);
		if (free_q_head == ASC_QLINK_END)
			break;
	}
	return free_q_head;
}