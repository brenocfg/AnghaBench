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
struct inode {int dummy; } ;
struct file {struct drm_dp_aux_dev* private_data; } ;
struct drm_dp_aux_dev {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_drm_dp_aux_dev ; 

__attribute__((used)) static int auxdev_release(struct inode *inode, struct file *file)
{
	struct drm_dp_aux_dev *aux_dev = file->private_data;

	kref_put(&aux_dev->refcount, release_drm_dp_aux_dev);
	return 0;
}