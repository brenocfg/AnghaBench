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
struct qxl_device {TYPE_1__* rom; } ;
struct drm_qxl_clientcap {int index; } ;
struct drm_file {int dummy; } ;
struct drm_device {TYPE_2__* pdev; struct qxl_device* dev_private; } ;
struct TYPE_4__ {int revision; } ;
struct TYPE_3__ {int* client_capabilities; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int qxl_clientcap_ioctl(struct drm_device *dev, void *data,
				  struct drm_file *file_priv)
{
	struct qxl_device *qdev = dev->dev_private;
	struct drm_qxl_clientcap *param = data;
	int byte, idx;

	byte = param->index / 8;
	idx = param->index % 8;

	if (dev->pdev->revision < 4)
		return -ENOSYS;

	if (byte >= 58)
		return -ENOSYS;

	if (qdev->rom->client_capabilities[byte] & (1 << idx))
		return 0;
	return -ENOSYS;
}