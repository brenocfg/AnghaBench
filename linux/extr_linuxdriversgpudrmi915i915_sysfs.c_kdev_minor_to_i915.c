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
struct drm_minor {int /*<<< orphan*/  dev; } ;
struct drm_i915_private {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_minor* dev_get_drvdata (struct device*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct drm_i915_private *kdev_minor_to_i915(struct device *kdev)
{
	struct drm_minor *minor = dev_get_drvdata(kdev);
	return to_i915(minor->dev);
}