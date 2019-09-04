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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; struct omap_vout_device* vm_private_data; } ;
struct omap_vout_device {int /*<<< orphan*/  mmap_count; TYPE_1__* vid_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_vout_vm_close(struct vm_area_struct *vma)
{
	struct omap_vout_device *vout = vma->vm_private_data;

	v4l2_dbg(1, debug, &vout->vid_dev->v4l2_dev,
		"vm_close [vma=%08lx-%08lx]\n", vma->vm_start, vma->vm_end);
	vout->mmap_count--;
}