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
struct ni_gpct {int /*<<< orphan*/  counter_index; } ;

/* Variables and functions */
 unsigned int GI_BITS_TO_GATE2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_GATE2_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_get_soft_copy (struct ni_gpct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int ni_tio_get_gate2_val(struct ni_gpct *counter)
{
	return GI_BITS_TO_GATE2(ni_tio_get_soft_copy(counter,
		NITIO_GATE2_REG(counter->counter_index)));
}