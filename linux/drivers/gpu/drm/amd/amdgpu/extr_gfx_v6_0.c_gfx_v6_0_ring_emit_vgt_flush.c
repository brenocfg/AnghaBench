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
struct amdgpu_ring {int dummy; } ;

/* Variables and functions */
 int EVENT_INDEX (int /*<<< orphan*/ ) ; 
 int EVENT_TYPE (int /*<<< orphan*/ ) ; 
 int PACKET3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_EVENT_WRITE ; 
 int /*<<< orphan*/  VGT_FLUSH ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 

__attribute__((used)) static void gfx_v6_0_ring_emit_vgt_flush(struct amdgpu_ring *ring)
{
	amdgpu_ring_write(ring, PACKET3(PACKET3_EVENT_WRITE, 0));
	amdgpu_ring_write(ring, EVENT_TYPE(VGT_FLUSH) |
		EVENT_INDEX(0));
}