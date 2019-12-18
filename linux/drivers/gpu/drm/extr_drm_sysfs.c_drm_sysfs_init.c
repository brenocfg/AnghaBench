#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  attr; } ;
struct TYPE_9__ {int /*<<< orphan*/  devnode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_6__ class_attr_version ; 
 TYPE_1__* class_create (int /*<<< orphan*/ ,char*) ; 
 int class_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (TYPE_1__*) ; 
 TYPE_1__* drm_class ; 
 int /*<<< orphan*/  drm_devnode ; 
 int /*<<< orphan*/  drm_setup_hdcp_srm (TYPE_1__*) ; 

int drm_sysfs_init(void)
{
	int err;

	drm_class = class_create(THIS_MODULE, "drm");
	if (IS_ERR(drm_class))
		return PTR_ERR(drm_class);

	err = class_create_file(drm_class, &class_attr_version.attr);
	if (err) {
		class_destroy(drm_class);
		drm_class = NULL;
		return err;
	}

	drm_class->devnode = drm_devnode;
	drm_setup_hdcp_srm(drm_class);
	return 0;
}