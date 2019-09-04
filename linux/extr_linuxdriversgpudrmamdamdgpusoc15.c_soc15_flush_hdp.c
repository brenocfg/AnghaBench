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
struct amdgpu_ring {int dummy; } ;
struct amdgpu_device {TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hdp_flush ) (struct amdgpu_device*,struct amdgpu_ring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,struct amdgpu_ring*) ; 

__attribute__((used)) static void soc15_flush_hdp(struct amdgpu_device *adev, struct amdgpu_ring *ring)
{
	adev->nbio_funcs->hdp_flush(adev, ring);
}