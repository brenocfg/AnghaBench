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
struct drm_omap_param {int param; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int EINVAL ; 

__attribute__((used)) static int ioctl_set_param(struct drm_device *dev, void *data,
		struct drm_file *file_priv)
{
	struct drm_omap_param *args = data;

	switch (args->param) {
	default:
		DBG("unknown parameter %lld", args->param);
		return -EINVAL;
	}

	return 0;
}