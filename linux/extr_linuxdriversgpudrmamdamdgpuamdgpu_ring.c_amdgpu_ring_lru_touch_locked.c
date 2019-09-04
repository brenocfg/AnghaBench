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
struct amdgpu_ring {int /*<<< orphan*/  lru_list; } ;
struct amdgpu_device {int /*<<< orphan*/  ring_lru_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_ring_lru_touch_locked(struct amdgpu_device *adev,
					 struct amdgpu_ring *ring)
{
	/* list_move_tail handles the case where ring isn't part of the list */
	list_move_tail(&ring->lru_list, &adev->ring_lru_list);
}