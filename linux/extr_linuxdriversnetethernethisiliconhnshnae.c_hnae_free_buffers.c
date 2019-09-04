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
struct hnae_ring {int desc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  hnae_free_buffer_detach (struct hnae_ring*,int) ; 

__attribute__((used)) static void hnae_free_buffers(struct hnae_ring *ring)
{
	int i;

	for (i = 0; i < ring->desc_num; i++)
		hnae_free_buffer_detach(ring, i);
}