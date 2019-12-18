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
struct intel_guc_client {int dummy; } ;
struct guc_doorbell_info {scalar_t__ cookie; int /*<<< orphan*/  db_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_DOORBELL_ENABLED ; 
 struct guc_doorbell_info* __get_doorbell (struct intel_guc_client*) ; 

__attribute__((used)) static void __init_doorbell(struct intel_guc_client *client)
{
	struct guc_doorbell_info *doorbell;

	doorbell = __get_doorbell(client);
	doorbell->db_status = GUC_DOORBELL_ENABLED;
	doorbell->cookie = 0;
}