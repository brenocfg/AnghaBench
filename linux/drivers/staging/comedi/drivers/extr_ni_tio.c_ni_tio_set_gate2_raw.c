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
 int /*<<< orphan*/  GI_GATE2_SEL (unsigned int) ; 
 int /*<<< orphan*/  GI_GATE2_SEL_MASK ; 
 int /*<<< orphan*/  NITIO_GATE2_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ni_tio_set_gate2_raw(struct ni_gpct *counter,
					unsigned int gate_source)
{
	ni_tio_set_bits(counter, NITIO_GATE2_REG(counter->counter_index),
			GI_GATE2_SEL_MASK, GI_GATE2_SEL(gate_source));
}