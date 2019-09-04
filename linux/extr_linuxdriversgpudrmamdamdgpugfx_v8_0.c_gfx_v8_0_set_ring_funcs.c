#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_9__ {TYPE_3__ ring; } ;
struct TYPE_10__ {int num_gfx_rings; int num_compute_rings; TYPE_2__* compute_ring; TYPE_1__* gfx_ring; TYPE_4__ kiq; } ;
struct amdgpu_device {TYPE_5__ gfx; } ;
struct TYPE_7__ {int /*<<< orphan*/ * funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/ * funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfx_v8_0_ring_funcs_compute ; 
 int /*<<< orphan*/  gfx_v8_0_ring_funcs_gfx ; 
 int /*<<< orphan*/  gfx_v8_0_ring_funcs_kiq ; 

__attribute__((used)) static void gfx_v8_0_set_ring_funcs(struct amdgpu_device *adev)
{
	int i;

	adev->gfx.kiq.ring.funcs = &gfx_v8_0_ring_funcs_kiq;

	for (i = 0; i < adev->gfx.num_gfx_rings; i++)
		adev->gfx.gfx_ring[i].funcs = &gfx_v8_0_ring_funcs_gfx;

	for (i = 0; i < adev->gfx.num_compute_rings; i++)
		adev->gfx.compute_ring[i].funcs = &gfx_v8_0_ring_funcs_compute;
}