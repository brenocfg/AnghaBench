#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct drm_file {TYPE_2__* minor; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_3__ {struct drm_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_vm_open_locked (struct drm_device*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drm_vm_open(struct vm_area_struct *vma)
{
	struct drm_file *priv = vma->vm_file->private_data;
	struct drm_device *dev = priv->minor->dev;

	mutex_lock(&dev->struct_mutex);
	drm_vm_open_locked(dev, vma);
	mutex_unlock(&dev->struct_mutex);
}