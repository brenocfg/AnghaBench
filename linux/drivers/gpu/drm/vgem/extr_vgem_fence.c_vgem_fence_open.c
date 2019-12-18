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
struct vgem_file {int /*<<< orphan*/  fence_idr; int /*<<< orphan*/  fence_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int vgem_fence_open(struct vgem_file *vfile)
{
	mutex_init(&vfile->fence_mutex);
	idr_init(&vfile->fence_idr);

	return 0;
}