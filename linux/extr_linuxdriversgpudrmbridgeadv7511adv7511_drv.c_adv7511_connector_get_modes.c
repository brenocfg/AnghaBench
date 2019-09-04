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
struct adv7511 {int dummy; } ;

/* Variables and functions */
 int adv7511_get_modes (struct adv7511*,struct drm_connector*) ; 
 struct adv7511* connector_to_adv7511 (struct drm_connector*) ; 

__attribute__((used)) static int adv7511_connector_get_modes(struct drm_connector *connector)
{
	struct adv7511 *adv = connector_to_adv7511(connector);

	return adv7511_get_modes(adv, connector);
}