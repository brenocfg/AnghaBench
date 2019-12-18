#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ kobj; } ;
struct TYPE_8__ {TYPE_3__ dev; } ;
struct intel_sdvo {TYPE_4__ ddc; } ;
struct drm_connector {TYPE_1__* kdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 struct intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_sdvo_connector_unregister(struct drm_connector *connector)
{
	struct intel_sdvo *sdvo = intel_attached_sdvo(connector);

	sysfs_remove_link(&connector->kdev->kobj,
			  sdvo->ddc.dev.kobj.name);
	intel_connector_unregister(connector);
}