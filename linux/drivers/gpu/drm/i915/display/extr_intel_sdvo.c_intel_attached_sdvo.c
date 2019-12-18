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
struct intel_sdvo {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_attached_encoder (struct drm_connector*) ; 
 struct intel_sdvo* to_sdvo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct intel_sdvo *intel_attached_sdvo(struct drm_connector *connector)
{
	return to_sdvo(intel_attached_encoder(connector));
}