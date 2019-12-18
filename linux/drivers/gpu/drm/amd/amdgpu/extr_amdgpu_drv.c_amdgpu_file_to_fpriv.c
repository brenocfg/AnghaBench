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
struct file {struct drm_file* private_data; int /*<<< orphan*/ * f_op; } ;
struct drm_file {struct amdgpu_fpriv* driver_priv; } ;
struct amdgpu_fpriv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_driver_kms_fops ; 

int amdgpu_file_to_fpriv(struct file *filp, struct amdgpu_fpriv **fpriv)
{
        struct drm_file *file;

	if (!filp)
		return -EINVAL;

	if (filp->f_op != &amdgpu_driver_kms_fops) {
		return -EINVAL;
	}

	file = filp->private_data;
	*fpriv = file->driver_priv;
	return 0;
}