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
struct transmit_ring {int /*<<< orphan*/  lastRead; int /*<<< orphan*/  lastWrite; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXLO_ENTRIES ; 
 int typhoon_num_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
typhoon_num_free_tx(struct transmit_ring *ring)
{
	/* if we start using the Hi Tx ring, this needs updating */
	return typhoon_num_free(ring->lastWrite, ring->lastRead, TXLO_ENTRIES);
}