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
struct amdgpu_device {int /*<<< orphan*/  ring_lru_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_ring_lru_touch_locked (struct amdgpu_device*,struct amdgpu_ring*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void amdgpu_ring_lru_touch(struct amdgpu_device *adev, struct amdgpu_ring *ring)
{
	spin_lock(&adev->ring_lru_list_lock);
	amdgpu_ring_lru_touch_locked(adev, ring);
	spin_unlock(&adev->ring_lru_list_lock);
}