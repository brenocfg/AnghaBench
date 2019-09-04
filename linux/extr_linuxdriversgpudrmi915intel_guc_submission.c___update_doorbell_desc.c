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
struct intel_guc_client {int dummy; } ;
struct guc_stage_desc {int /*<<< orphan*/  db_id; } ;

/* Variables and functions */
 struct guc_stage_desc* __get_stage_desc (struct intel_guc_client*) ; 

__attribute__((used)) static void __update_doorbell_desc(struct intel_guc_client *client, u16 new_id)
{
	struct guc_stage_desc *desc;

	/* Update the GuC's idea of the doorbell ID */
	desc = __get_stage_desc(client);
	desc->db_id = new_id;
}