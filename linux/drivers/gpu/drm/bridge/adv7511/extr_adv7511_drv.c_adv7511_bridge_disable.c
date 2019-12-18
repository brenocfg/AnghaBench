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
struct adv7511 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv7511_power_off (struct adv7511*) ; 
 struct adv7511* bridge_to_adv7511 (struct drm_bridge*) ; 

__attribute__((used)) static void adv7511_bridge_disable(struct drm_bridge *bridge)
{
	struct adv7511 *adv = bridge_to_adv7511(bridge);

	adv7511_power_off(adv);
}