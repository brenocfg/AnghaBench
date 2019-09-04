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
struct i915_oa_config {int /*<<< orphan*/  ref_count; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_oa_config (struct drm_i915_private*,struct i915_oa_config*) ; 

__attribute__((used)) static void put_oa_config(struct drm_i915_private *dev_priv,
			  struct i915_oa_config *oa_config)
{
	if (!atomic_dec_and_test(&oa_config->ref_count))
		return;

	free_oa_config(dev_priv, oa_config);
}