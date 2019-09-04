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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  master; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* master_drop ) (struct drm_device*,struct drm_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_master_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,struct drm_file*) ; 

__attribute__((used)) static void drm_drop_master(struct drm_device *dev,
			    struct drm_file *fpriv)
{
	if (dev->driver->master_drop)
		dev->driver->master_drop(dev, fpriv);
	drm_master_put(&dev->master);
}