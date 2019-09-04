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
typedef  size_t u32 ;
struct octeon_device {TYPE_1__** instr_queue; } ;
struct TYPE_2__ {int max_count; int /*<<< orphan*/  instr_pending; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int octnet_iq_is_full(struct octeon_device *oct, u32 q_no)
{
	return ((u32)atomic_read(&oct->instr_queue[q_no]->instr_pending)
		>= (oct->instr_queue[q_no]->max_count - 2));
}