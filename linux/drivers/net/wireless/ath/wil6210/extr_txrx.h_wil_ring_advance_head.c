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
struct wil_ring {int swhead; int size; } ;

/* Variables and functions */

__attribute__((used)) static inline void wil_ring_advance_head(struct wil_ring *ring, int n)
{
	ring->swhead = (ring->swhead + n) % ring->size;
}