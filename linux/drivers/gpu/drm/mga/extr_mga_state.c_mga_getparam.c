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
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* pdev; TYPE_2__* dev_private; } ;
struct TYPE_5__ {int chipset; } ;
typedef  TYPE_2__ drm_mga_private_t ;
struct TYPE_6__ {int param; int /*<<< orphan*/  value; } ;
typedef  TYPE_3__ drm_mga_getparam_t ;
struct TYPE_4__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EFAULT ; 
 int EINVAL ; 
#define  MGA_PARAM_CARD_TYPE 129 
#define  MGA_PARAM_IRQ_NR 128 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

int mga_getparam(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_getparam_t *param = data;
	int value;

	if (!dev_priv) {
		DRM_ERROR("called with no initialization\n");
		return -EINVAL;
	}

	DRM_DEBUG("pid=%d\n", task_pid_nr(current));

	switch (param->param) {
	case MGA_PARAM_IRQ_NR:
		value = dev->pdev->irq;
		break;
	case MGA_PARAM_CARD_TYPE:
		value = dev_priv->chipset;
		break;
	default:
		return -EINVAL;
	}

	if (copy_to_user(param->value, &value, sizeof(int))) {
		DRM_ERROR("copy_to_user\n");
		return -EFAULT;
	}

	return 0;
}