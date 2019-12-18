#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  queue_bitmap; } ;
struct TYPE_4__ {TYPE_1__ me; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_gfx_me_queue_to_bit (struct amdgpu_device*,int,int,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool amdgpu_gfx_is_me_queue_enabled(struct amdgpu_device *adev,
				    int me, int pipe, int queue)
{
	return test_bit(amdgpu_gfx_me_queue_to_bit(adev, me, pipe, queue),
			adev->gfx.me.queue_bitmap);
}