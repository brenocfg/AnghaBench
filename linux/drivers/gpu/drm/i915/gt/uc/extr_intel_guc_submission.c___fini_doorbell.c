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
struct intel_guc_client {int /*<<< orphan*/  guc; int /*<<< orphan*/  doorbell_id; } ;
struct guc_doorbell_info {int /*<<< orphan*/  db_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_DOORBELL_DISABLED ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  __doorbell_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct guc_doorbell_info* __get_doorbell (struct intel_guc_client*) ; 
 scalar_t__ wait_for_us (int,int) ; 

__attribute__((used)) static void __fini_doorbell(struct intel_guc_client *client)
{
	struct guc_doorbell_info *doorbell;
	u16 db_id = client->doorbell_id;

	doorbell = __get_doorbell(client);
	doorbell->db_status = GUC_DOORBELL_DISABLED;

	/* Doorbell release flow requires that we wait for GEN8_DRB_VALID bit
	 * to go to zero after updating db_status before we call the GuC to
	 * release the doorbell
	 */
	if (wait_for_us(!__doorbell_valid(client->guc, db_id), 10))
		WARN_ONCE(true, "Doorbell never became invalid after disable\n");
}