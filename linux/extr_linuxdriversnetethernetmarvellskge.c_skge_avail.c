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
struct skge_ring {scalar_t__ to_clean; scalar_t__ to_use; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static inline int skge_avail(const struct skge_ring *ring)
{
	smp_mb();
	return ((ring->to_clean > ring->to_use) ? 0 : ring->count)
		+ (ring->to_clean - ring->to_use) - 1;
}