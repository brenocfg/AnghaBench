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
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdv_intel_attach_broadcast_rgb_property (struct drm_connector*) ; 
 int /*<<< orphan*/  cdv_intel_attach_force_audio_property (struct drm_connector*) ; 

__attribute__((used)) static void cdv_intel_dp_add_properties(struct drm_connector *connector)
{
	cdv_intel_attach_force_audio_property(connector);
	cdv_intel_attach_broadcast_rgb_property(connector);
}