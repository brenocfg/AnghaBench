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

__attribute__((used)) static void uvd_v6_0_ring_emit_hdp_flush(struct amdgpu_ring *ring)
{
	/* The firmware doesn't seem to like touching registers at this point. */
}