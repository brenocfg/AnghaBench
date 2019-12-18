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
struct amdgpu_device {TYPE_1__* nbio_funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_doorbell_selfring_aperture ) (struct amdgpu_device*,int) ;int /*<<< orphan*/  (* enable_doorbell_aperture ) (struct amdgpu_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*,int) ; 

__attribute__((used)) static void nv_enable_doorbell_aperture(struct amdgpu_device *adev,
					bool enable)
{
	adev->nbio_funcs->enable_doorbell_aperture(adev, enable);
	adev->nbio_funcs->enable_doorbell_selfring_aperture(adev, enable);
}