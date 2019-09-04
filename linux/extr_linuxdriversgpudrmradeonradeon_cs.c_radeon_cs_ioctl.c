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
struct radeon_device {int /*<<< orphan*/  exclusive_lock; int /*<<< orphan*/  family; int /*<<< orphan*/  dev; scalar_t__ in_reset; int /*<<< orphan*/  accel_working; } ;
struct radeon_cs_parser {int /*<<< orphan*/  family; int /*<<< orphan*/  dev; struct radeon_device* rdev; struct drm_file* filp; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct radeon_cs_parser*,int /*<<< orphan*/ ,int) ; 
 int radeon_cs_handle_lockup (struct radeon_device*,int) ; 
 int radeon_cs_ib_chunk (struct radeon_device*,struct radeon_cs_parser*) ; 
 int radeon_cs_ib_fill (struct radeon_device*,struct radeon_cs_parser*) ; 
 int radeon_cs_ib_vm_chunk (struct radeon_device*,struct radeon_cs_parser*) ; 
 int /*<<< orphan*/  radeon_cs_parser_fini (struct radeon_cs_parser*,int,int) ; 
 int radeon_cs_parser_init (struct radeon_cs_parser*,void*) ; 
 int radeon_cs_parser_relocs (struct radeon_cs_parser*) ; 
 int radeon_gpu_reset (struct radeon_device*) ; 
 int /*<<< orphan*/  trace_radeon_cs (struct radeon_cs_parser*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int radeon_cs_ioctl(struct drm_device *dev, void *data, struct drm_file *filp)
{
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_cs_parser parser;
	int r;

	down_read(&rdev->exclusive_lock);
	if (!rdev->accel_working) {
		up_read(&rdev->exclusive_lock);
		return -EBUSY;
	}
	if (rdev->in_reset) {
		up_read(&rdev->exclusive_lock);
		r = radeon_gpu_reset(rdev);
		if (!r)
			r = -EAGAIN;
		return r;
	}
	/* initialize parser */
	memset(&parser, 0, sizeof(struct radeon_cs_parser));
	parser.filp = filp;
	parser.rdev = rdev;
	parser.dev = rdev->dev;
	parser.family = rdev->family;
	r = radeon_cs_parser_init(&parser, data);
	if (r) {
		DRM_ERROR("Failed to initialize parser !\n");
		radeon_cs_parser_fini(&parser, r, false);
		up_read(&rdev->exclusive_lock);
		r = radeon_cs_handle_lockup(rdev, r);
		return r;
	}

	r = radeon_cs_ib_fill(rdev, &parser);
	if (!r) {
		r = radeon_cs_parser_relocs(&parser);
		if (r && r != -ERESTARTSYS)
			DRM_ERROR("Failed to parse relocation %d!\n", r);
	}

	if (r) {
		radeon_cs_parser_fini(&parser, r, false);
		up_read(&rdev->exclusive_lock);
		r = radeon_cs_handle_lockup(rdev, r);
		return r;
	}

	trace_radeon_cs(&parser);

	r = radeon_cs_ib_chunk(rdev, &parser);
	if (r) {
		goto out;
	}
	r = radeon_cs_ib_vm_chunk(rdev, &parser);
	if (r) {
		goto out;
	}
out:
	radeon_cs_parser_fini(&parser, r, true);
	up_read(&rdev->exclusive_lock);
	r = radeon_cs_handle_lockup(rdev, r);
	return r;
}