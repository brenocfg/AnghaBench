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
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mdev_dev (int /*<<< orphan*/ ) ; 
 int roundup (unsigned long,int) ; 
 int vfio_unpin_pages (int /*<<< orphan*/ ,unsigned long*,int) ; 

__attribute__((used)) static void gvt_unpin_guest_page(struct intel_vgpu *vgpu, unsigned long gfn,
		unsigned long size)
{
	int total_pages;
	int npage;
	int ret;

	total_pages = roundup(size, PAGE_SIZE) / PAGE_SIZE;

	for (npage = 0; npage < total_pages; npage++) {
		unsigned long cur_gfn = gfn + npage;

		ret = vfio_unpin_pages(mdev_dev(vgpu->vdev.mdev), &cur_gfn, 1);
		WARN_ON(ret != 1);
	}
}