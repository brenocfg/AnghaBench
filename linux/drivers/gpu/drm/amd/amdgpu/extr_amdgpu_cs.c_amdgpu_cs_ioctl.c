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
typedef  union drm_amdgpu_cs {int dummy; } drm_amdgpu_cs ;
struct drm_file {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct amdgpu_device {int /*<<< orphan*/  accel_working; } ;
struct amdgpu_cs_parser {TYPE_1__* job; struct drm_file* filp; struct amdgpu_device* adev; } ;
struct TYPE_2__ {int num_ibs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int amdgpu_cs_dependencies (struct amdgpu_device*,struct amdgpu_cs_parser*) ; 
 int amdgpu_cs_ib_fill (struct amdgpu_device*,struct amdgpu_cs_parser*) ; 
 int amdgpu_cs_parser_bos (struct amdgpu_cs_parser*,void*) ; 
 int /*<<< orphan*/  amdgpu_cs_parser_fini (struct amdgpu_cs_parser*,int,int) ; 
 int amdgpu_cs_parser_init (struct amdgpu_cs_parser*,void*) ; 
 int amdgpu_cs_submit (struct amdgpu_cs_parser*,union drm_amdgpu_cs*) ; 
 int amdgpu_cs_vm_handling (struct amdgpu_cs_parser*) ; 
 int /*<<< orphan*/  trace_amdgpu_cs (struct amdgpu_cs_parser*,int) ; 

int amdgpu_cs_ioctl(struct drm_device *dev, void *data, struct drm_file *filp)
{
	struct amdgpu_device *adev = dev->dev_private;
	union drm_amdgpu_cs *cs = data;
	struct amdgpu_cs_parser parser = {};
	bool reserved_buffers = false;
	int i, r;

	if (!adev->accel_working)
		return -EBUSY;

	parser.adev = adev;
	parser.filp = filp;

	r = amdgpu_cs_parser_init(&parser, data);
	if (r) {
		DRM_ERROR("Failed to initialize parser %d!\n", r);
		goto out;
	}

	r = amdgpu_cs_ib_fill(adev, &parser);
	if (r)
		goto out;

	r = amdgpu_cs_dependencies(adev, &parser);
	if (r) {
		DRM_ERROR("Failed in the dependencies handling %d!\n", r);
		goto out;
	}

	r = amdgpu_cs_parser_bos(&parser, data);
	if (r) {
		if (r == -ENOMEM)
			DRM_ERROR("Not enough memory for command submission!\n");
		else if (r != -ERESTARTSYS && r != -EAGAIN)
			DRM_ERROR("Failed to process the buffer list %d!\n", r);
		goto out;
	}

	reserved_buffers = true;

	for (i = 0; i < parser.job->num_ibs; i++)
		trace_amdgpu_cs(&parser, i);

	r = amdgpu_cs_vm_handling(&parser);
	if (r)
		goto out;

	r = amdgpu_cs_submit(&parser, cs);

out:
	amdgpu_cs_parser_fini(&parser, r, reserved_buffers);

	return r;
}