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
struct amdgpu_ring {int buf_mask; TYPE_1__* funcs; int /*<<< orphan*/ * ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  nop; } ;

/* Variables and functions */

__attribute__((used)) static inline void amdgpu_ring_clear_ring(struct amdgpu_ring *ring)
{
	int i = 0;
	while (i <= ring->buf_mask)
		ring->ring[i++] = ring->funcs->nop;

}