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
struct drm_bridge {int dummy; } ;
struct anx78xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int anx78xx_set_hpd (struct anx78xx*) ; 
 int anx78xx_start (struct anx78xx*) ; 
 struct anx78xx* bridge_to_anx78xx (struct drm_bridge*) ; 

__attribute__((used)) static void anx78xx_bridge_enable(struct drm_bridge *bridge)
{
	struct anx78xx *anx78xx = bridge_to_anx78xx(bridge);
	int err;

	err = anx78xx_start(anx78xx);
	if (err) {
		DRM_ERROR("Failed to initialize: %d\n", err);
		return;
	}

	err = anx78xx_set_hpd(anx78xx);
	if (err)
		DRM_ERROR("Failed to set HPD: %d\n", err);
}