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
typedef  int /*<<< orphan*/  u32 ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int msm_submitqueue_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msm_ioctl_submitqueue_close(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	u32 id = *(u32 *) data;

	return msm_submitqueue_remove(file->driver_priv, id);
}