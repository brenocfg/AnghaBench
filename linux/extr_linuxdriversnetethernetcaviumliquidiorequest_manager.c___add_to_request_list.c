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
struct octeon_instr_queue {TYPE_1__* request_list; } ;
struct TYPE_2__ {int reqtype; void* buf; } ;

/* Variables and functions */

__attribute__((used)) static inline void
__add_to_request_list(struct octeon_instr_queue *iq,
		      int idx, void *buf, int reqtype)
{
	iq->request_list[idx].buf = buf;
	iq->request_list[idx].reqtype = reqtype;
}