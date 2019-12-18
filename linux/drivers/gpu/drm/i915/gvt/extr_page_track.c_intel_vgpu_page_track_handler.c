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
typedef  int u64 ;
struct intel_vgpu_page_track {int (* handler ) (struct intel_vgpu_page_track*,int,void*,unsigned int) ;} ;
struct intel_vgpu {int /*<<< orphan*/  vgpu_lock; int /*<<< orphan*/  failsafe; } ;

/* Variables and functions */
 int ENXIO ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  gvt_err (char*,int) ; 
 int /*<<< orphan*/  intel_vgpu_disable_page_track (struct intel_vgpu*,int) ; 
 struct intel_vgpu_page_track* intel_vgpu_find_page_track (struct intel_vgpu*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct intel_vgpu_page_track*,int,void*,unsigned int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int intel_vgpu_page_track_handler(struct intel_vgpu *vgpu, u64 gpa,
		void *data, unsigned int bytes)
{
	struct intel_vgpu_page_track *page_track;
	int ret = 0;

	mutex_lock(&vgpu->vgpu_lock);

	page_track = intel_vgpu_find_page_track(vgpu, gpa >> PAGE_SHIFT);
	if (!page_track) {
		ret = -ENXIO;
		goto out;
	}

	if (unlikely(vgpu->failsafe)) {
		/* Remove write protection to prevent furture traps. */
		intel_vgpu_disable_page_track(vgpu, gpa >> PAGE_SHIFT);
	} else {
		ret = page_track->handler(page_track, gpa, data, bytes);
		if (ret)
			gvt_err("guest page write error, gpa %llx\n", gpa);
	}

out:
	mutex_unlock(&vgpu->vgpu_lock);
	return ret;
}