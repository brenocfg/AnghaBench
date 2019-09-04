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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOMAIN_AUDIO ; 
 int /*<<< orphan*/  intel_display_power_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdev_to_i915 (struct device*) ; 

__attribute__((used)) static void i915_audio_component_put_power(struct device *kdev)
{
	intel_display_power_put(kdev_to_i915(kdev), POWER_DOMAIN_AUDIO);
}