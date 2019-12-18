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
struct octeon_instr_queue {int iqcmd_64B; } ;
struct octeon_device {scalar_t__* instr_queue; } ;

/* Variables and functions */

__attribute__((used)) static inline int IQ_INSTR_MODE_64B(struct octeon_device *oct, int iq_no)
{
	struct octeon_instr_queue *iq =
	    (struct octeon_instr_queue *)oct->instr_queue[iq_no];
	return iq->iqcmd_64B;
}