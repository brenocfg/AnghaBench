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
 int /*<<< orphan*/  FRAME_CMD (int) ; 
 int /*<<< orphan*/  PACKET3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKET3_FRAME_CONTROL ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_v9_0_ring_emit_tmz(struct amdgpu_ring *ring, bool start)
{
	amdgpu_ring_write(ring, PACKET3(PACKET3_FRAME_CONTROL, 0));
	amdgpu_ring_write(ring, FRAME_CMD(start ? 0 : 1)); /* frame_end */
}