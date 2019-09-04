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
typedef  int /*<<< orphan*/  u16 ;
struct intel_guc_client {int /*<<< orphan*/  doorbell_id; int /*<<< orphan*/  guc; } ;
struct guc_doorbell_info {scalar_t__ cookie; int /*<<< orphan*/  db_status; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_DRBREGL (int /*<<< orphan*/ ) ; 
 int GEN8_DRB_VALID ; 
 int /*<<< orphan*/  GUC_DOORBELL_DISABLED ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct guc_doorbell_info* __get_doorbell (struct intel_guc_client*) ; 
 struct drm_i915_private* guc_to_i915 (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_us (int,int) ; 

__attribute__((used)) static void __destroy_doorbell(struct intel_guc_client *client)
{
	struct drm_i915_private *dev_priv = guc_to_i915(client->guc);
	struct guc_doorbell_info *doorbell;
	u16 db_id = client->doorbell_id;

	doorbell = __get_doorbell(client);
	doorbell->db_status = GUC_DOORBELL_DISABLED;
	doorbell->cookie = 0;

	/* Doorbell release flow requires that we wait for GEN8_DRB_VALID bit
	 * to go to zero after updating db_status before we call the GuC to
	 * release the doorbell
	 */
	if (wait_for_us(!(I915_READ(GEN8_DRBREGL(db_id)) & GEN8_DRB_VALID), 10))
		WARN_ONCE(true, "Doorbell never became invalid after disable\n");
}