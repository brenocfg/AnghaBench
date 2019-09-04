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
struct vmw_master {int dummy; } ;
struct drm_master {int /*<<< orphan*/ * driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vmw_master*) ; 
 struct vmw_master* vmw_master (struct drm_master*) ; 

__attribute__((used)) static void vmw_master_destroy(struct drm_device *dev,
			       struct drm_master *master)
{
	struct vmw_master *vmaster = vmw_master(master);

	master->driver_priv = NULL;
	kfree(vmaster);
}