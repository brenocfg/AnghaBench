#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct intel_vgpu {TYPE_2__* gvt; } ;
struct TYPE_4__ {int /*<<< orphan*/  iomap; } ;
struct TYPE_6__ {TYPE_1__ ggtt; } ;
struct TYPE_5__ {TYPE_3__* dev_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_DOWN (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  gvt_vgpu_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  intel_vgpu_in_aperture (struct intel_vgpu*,scalar_t__) ; 
 void* io_mapping_map_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  io_mapping_unmap (void*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 int offset_in_page (scalar_t__) ; 

__attribute__((used)) static int intel_vgpu_aperture_rw(struct intel_vgpu *vgpu, uint64_t off,
		void *buf, unsigned long count, bool is_write)
{
	void *aperture_va;

	if (!intel_vgpu_in_aperture(vgpu, off) ||
	    !intel_vgpu_in_aperture(vgpu, off + count)) {
		gvt_vgpu_err("Invalid aperture offset %llu\n", off);
		return -EINVAL;
	}

	aperture_va = io_mapping_map_wc(&vgpu->gvt->dev_priv->ggtt.iomap,
					ALIGN_DOWN(off, PAGE_SIZE),
					count + offset_in_page(off));
	if (!aperture_va)
		return -EIO;

	if (is_write)
		memcpy(aperture_va + offset_in_page(off), buf, count);
	else
		memcpy(buf, aperture_va + offset_in_page(off), count);

	io_mapping_unmap(aperture_va);

	return 0;
}