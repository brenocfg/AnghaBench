#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ drm_via_cmdbuffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int via_dispatch_pci_cmdbuffer (struct drm_device*,TYPE_1__*) ; 

__attribute__((used)) static int via_pci_cmdbuffer(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_via_cmdbuffer_t *cmdbuf = data;
	int ret;

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DRM_DEBUG("buf %p size %lu\n", cmdbuf->buf, cmdbuf->size);

	ret = via_dispatch_pci_cmdbuffer(dev, cmdbuf);
	return ret;
}