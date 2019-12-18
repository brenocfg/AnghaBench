#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pm_qos; int /*<<< orphan*/  work; } ;
struct drm_i915_private {TYPE_1__ i945gm_vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i945gm_vblank_work_fini(struct drm_i915_private *dev_priv)
{
	cancel_work_sync(&dev_priv->i945gm_vblank.work);
	pm_qos_remove_request(&dev_priv->i945gm_vblank.pm_qos);
}