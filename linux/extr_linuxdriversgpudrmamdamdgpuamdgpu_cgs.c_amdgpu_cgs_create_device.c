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
struct cgs_device {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct amdgpu_cgs_device {struct amdgpu_device* adev; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_cgs_ops ; 
 struct amdgpu_cgs_device* kmalloc (int,int /*<<< orphan*/ ) ; 

struct cgs_device *amdgpu_cgs_create_device(struct amdgpu_device *adev)
{
	struct amdgpu_cgs_device *cgs_device =
		kmalloc(sizeof(*cgs_device), GFP_KERNEL);

	if (!cgs_device) {
		DRM_ERROR("Couldn't allocate CGS device structure\n");
		return NULL;
	}

	cgs_device->base.ops = &amdgpu_cgs_ops;
	cgs_device->adev = adev;

	return (struct cgs_device *)cgs_device;
}