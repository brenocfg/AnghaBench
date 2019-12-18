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
struct qxl_device {TYPE_1__* rom; } ;
struct drm_qxl_getparam {int param; int /*<<< orphan*/  value; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct qxl_device* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_surfaces; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QXL_MAX_RES ; 
#define  QXL_PARAM_MAX_RELOCS 129 
#define  QXL_PARAM_NUM_SURFACES 128 

__attribute__((used)) static int qxl_getparam_ioctl(struct drm_device *dev, void *data,
		       struct drm_file *file_priv)
{
	struct qxl_device *qdev = dev->dev_private;
	struct drm_qxl_getparam *param = data;

	switch (param->param) {
	case QXL_PARAM_NUM_SURFACES:
		param->value = qdev->rom->n_surfaces;
		break;
	case QXL_PARAM_MAX_RELOCS:
		param->value = QXL_MAX_RES;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}