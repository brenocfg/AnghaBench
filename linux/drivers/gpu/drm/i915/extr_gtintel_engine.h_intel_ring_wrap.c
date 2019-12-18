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
typedef  int u32 ;
struct intel_ring {int size; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 intel_ring_wrap(const struct intel_ring *ring, u32 pos)
{
	return pos & (ring->size - 1);
}