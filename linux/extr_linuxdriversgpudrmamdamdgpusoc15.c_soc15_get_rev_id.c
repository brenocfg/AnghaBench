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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_device {TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_rev_id ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static uint32_t soc15_get_rev_id(struct amdgpu_device *adev)
{
	return adev->nbio_funcs->get_rev_id(adev);
}