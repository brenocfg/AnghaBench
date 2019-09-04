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
struct intel_sdvo {int /*<<< orphan*/  ddc; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 struct edid* drm_get_edid (struct drm_connector*,int /*<<< orphan*/ *) ; 
 struct intel_sdvo* intel_attached_sdvo (struct drm_connector*) ; 

__attribute__((used)) static struct edid *
intel_sdvo_get_edid(struct drm_connector *connector)
{
	struct intel_sdvo *sdvo = intel_attached_sdvo(connector);
	return drm_get_edid(connector, &sdvo->ddc);
}