#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
struct TYPE_5__ {TYPE_1__ guc; } ;
struct TYPE_6__ {TYPE_2__ uc; } ;
struct drm_i915_private {TYPE_3__ gt; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USES_GUC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_guc_log_get_level (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i915_guc_log_level_get(void *data, u64 *val)
{
	struct drm_i915_private *dev_priv = data;

	if (!USES_GUC(dev_priv))
		return -ENODEV;

	*val = intel_guc_log_get_level(&dev_priv->gt.uc.guc.log);

	return 0;
}