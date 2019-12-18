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
struct tfp410 {int /*<<< orphan*/  powerdown; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct tfp410* drm_bridge_to_tfp410 (struct drm_bridge*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tfp410_enable(struct drm_bridge *bridge)
{
	struct tfp410 *dvi = drm_bridge_to_tfp410(bridge);

	gpiod_set_value_cansleep(dvi->powerdown, 0);
}