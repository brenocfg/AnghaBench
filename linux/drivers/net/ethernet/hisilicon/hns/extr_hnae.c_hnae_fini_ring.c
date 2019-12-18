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
struct hnae_ring {scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/ * desc_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  hnae_free_buffers (struct hnae_ring*) ; 
 int /*<<< orphan*/  hnae_free_desc (struct hnae_ring*) ; 
 scalar_t__ is_rx_ring (struct hnae_ring*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hnae_fini_ring(struct hnae_ring *ring)
{
	if (is_rx_ring(ring))
		hnae_free_buffers(ring);

	hnae_free_desc(ring);
	kfree(ring->desc_cb);
	ring->desc_cb = NULL;
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
}