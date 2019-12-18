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
typedef  int uint32_t ;
struct amdgpu_ring {int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; int /*<<< orphan*/  me; } ;
struct amdgpu_device {int /*<<< orphan*/  srbm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_SOC15_RLC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmCP_HQD_PIPE_PRIORITY ; 
 int /*<<< orphan*/  mmCP_HQD_QUEUE_PRIORITY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc15_grbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfx_v9_0_hqd_set_priority(struct amdgpu_device *adev,
				      struct amdgpu_ring *ring,
				      bool acquire)
{
	uint32_t pipe_priority = acquire ? 0x2 : 0x0;
	uint32_t queue_priority = acquire ? 0xf : 0x0;

	mutex_lock(&adev->srbm_mutex);
	soc15_grbm_select(adev, ring->me, ring->pipe, ring->queue, 0);

	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_PIPE_PRIORITY, pipe_priority);
	WREG32_SOC15_RLC(GC, 0, mmCP_HQD_QUEUE_PRIORITY, queue_priority);

	soc15_grbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);
}