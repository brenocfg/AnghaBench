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
struct TYPE_3__ {int num_pipe_per_mec; int num_queue_per_pipe; } ;
struct TYPE_4__ {TYPE_1__ mec; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */

__attribute__((used)) static inline int amdgpu_gfx_queue_to_bit(struct amdgpu_device *adev,
					  int mec, int pipe, int queue)
{
	int bit = 0;

	bit += mec * adev->gfx.mec.num_pipe_per_mec
		* adev->gfx.mec.num_queue_per_pipe;
	bit += pipe * adev->gfx.mec.num_queue_per_pipe;
	bit += queue;

	return bit;
}