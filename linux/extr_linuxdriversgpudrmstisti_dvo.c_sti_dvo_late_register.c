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
struct sti_dvo_connector {struct sti_dvo* dvo; } ;
struct sti_dvo {TYPE_1__* drm_dev; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ dvo_debugfs_init (struct sti_dvo*,int /*<<< orphan*/ ) ; 
 struct sti_dvo_connector* to_sti_dvo_connector (struct drm_connector*) ; 

__attribute__((used)) static int sti_dvo_late_register(struct drm_connector *connector)
{
	struct sti_dvo_connector *dvo_connector
		= to_sti_dvo_connector(connector);
	struct sti_dvo *dvo = dvo_connector->dvo;

	if (dvo_debugfs_init(dvo, dvo->drm_dev->primary)) {
		DRM_ERROR("DVO debugfs setup failed\n");
		return -EINVAL;
	}

	return 0;
}