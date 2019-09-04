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
struct i915_request {struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN6_BSD_RNCID ; 
 int /*<<< orphan*/  GEN6_BSD_SLEEP_INDICATOR ; 
 int /*<<< orphan*/  GEN6_BSD_SLEEP_MSG_DISABLE ; 
 int /*<<< orphan*/  GEN6_BSD_SLEEP_PSMI_CONTROL ; 
 int /*<<< orphan*/  I915_WRITE64_FW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I915_WRITE_FW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ __intel_wait_for_register_fw (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i9xx_submit_request (struct i915_request*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen6_bsd_submit_request(struct i915_request *request)
{
	struct drm_i915_private *dev_priv = request->i915;

	intel_uncore_forcewake_get(dev_priv, FORCEWAKE_ALL);

       /* Every tail move must follow the sequence below */

	/* Disable notification that the ring is IDLE. The GT
	 * will then assume that it is busy and bring it out of rc6.
	 */
	I915_WRITE_FW(GEN6_BSD_SLEEP_PSMI_CONTROL,
		      _MASKED_BIT_ENABLE(GEN6_BSD_SLEEP_MSG_DISABLE));

	/* Clear the context id. Here be magic! */
	I915_WRITE64_FW(GEN6_BSD_RNCID, 0x0);

	/* Wait for the ring not to be idle, i.e. for it to wake up. */
	if (__intel_wait_for_register_fw(dev_priv,
					 GEN6_BSD_SLEEP_PSMI_CONTROL,
					 GEN6_BSD_SLEEP_INDICATOR,
					 0,
					 1000, 0, NULL))
		DRM_ERROR("timed out waiting for the BSD ring to wake up\n");

	/* Now that the ring is fully powered up, update the tail */
	i9xx_submit_request(request);

	/* Let the ring send IDLE messages to the GT again,
	 * and so let it sleep to conserve power when idle.
	 */
	I915_WRITE_FW(GEN6_BSD_SLEEP_PSMI_CONTROL,
		      _MASKED_BIT_DISABLE(GEN6_BSD_SLEEP_MSG_DISABLE));

	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);
}