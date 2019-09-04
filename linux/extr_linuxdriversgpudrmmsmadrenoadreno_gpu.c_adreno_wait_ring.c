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
typedef  scalar_t__ uint32_t ;
struct msm_ringbuffer {int /*<<< orphan*/  id; TYPE_2__* gpu; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ring_freewords (struct msm_ringbuffer*) ; 
 scalar_t__ spin_until (int) ; 

void adreno_wait_ring(struct msm_ringbuffer *ring, uint32_t ndwords)
{
	if (spin_until(ring_freewords(ring) >= ndwords))
		DRM_DEV_ERROR(ring->gpu->dev->dev,
			"timeout waiting for space in ringbuffer %d\n",
			ring->id);
}