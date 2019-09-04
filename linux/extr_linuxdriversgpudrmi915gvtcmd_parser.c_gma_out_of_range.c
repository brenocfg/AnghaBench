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

/* Variables and functions */

__attribute__((used)) static inline bool gma_out_of_range(unsigned long gma,
		unsigned long gma_head, unsigned int gma_tail)
{
	if (gma_tail >= gma_head)
		return (gma < gma_head) || (gma > gma_tail);
	else
		return (gma > gma_tail) && (gma < gma_head);
}