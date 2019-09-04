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
struct sti_hda_connector {struct sti_hda* hda; } ;
struct sti_hda {TYPE_1__* drm_dev; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ hda_debugfs_init (struct sti_hda*,int /*<<< orphan*/ ) ; 
 struct sti_hda_connector* to_sti_hda_connector (struct drm_connector*) ; 

__attribute__((used)) static int sti_hda_late_register(struct drm_connector *connector)
{
	struct sti_hda_connector *hda_connector
		= to_sti_hda_connector(connector);
	struct sti_hda *hda = hda_connector->hda;

	if (hda_debugfs_init(hda, hda->drm_dev->primary)) {
		DRM_ERROR("HDA debugfs setup failed\n");
		return -EINVAL;
	}

	return 0;
}