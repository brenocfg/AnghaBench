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
struct acpi_gpe_xrupt_info {struct acpi_gpe_xrupt_info* next; struct acpi_gpe_block_info* gpe_block_list_head; } ;
struct acpi_gpe_walk_info {scalar_t__ count; int /*<<< orphan*/  gpe_device; struct acpi_gpe_block_info* gpe_block; int /*<<< orphan*/  execute_by_owner_id; int /*<<< orphan*/  owner_id; } ;
struct acpi_gpe_block_info {struct acpi_gpe_block_info* next; int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_owner_id ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int /*<<< orphan*/  ACPI_MTX_EVENTS ; 
 int /*<<< orphan*/  ACPI_NS_WALK_NO_UNLOCK ; 
 int /*<<< orphan*/  ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ev_match_gpe_method ; 
 struct acpi_gpe_xrupt_info* acpi_gbl_gpe_xrupt_list_head ; 
 int /*<<< orphan*/  acpi_ns_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_gpe_walk_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_acquire_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_release_mutex (int /*<<< orphan*/ ) ; 

void acpi_ev_update_gpes(acpi_owner_id table_owner_id)
{
	struct acpi_gpe_xrupt_info *gpe_xrupt_info;
	struct acpi_gpe_block_info *gpe_block;
	struct acpi_gpe_walk_info walk_info;
	acpi_status status = AE_OK;

	/*
	 * Find any _Lxx/_Exx GPE methods that have just been loaded.
	 *
	 * Any GPEs that correspond to new _Lxx/_Exx methods are immediately
	 * enabled.
	 *
	 * Examine the namespace underneath each gpe_device within the
	 * gpe_block lists.
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	if (ACPI_FAILURE(status)) {
		return;
	}

	walk_info.count = 0;
	walk_info.owner_id = table_owner_id;
	walk_info.execute_by_owner_id = TRUE;

	/* Walk the interrupt level descriptor list */

	gpe_xrupt_info = acpi_gbl_gpe_xrupt_list_head;
	while (gpe_xrupt_info) {

		/* Walk all Gpe Blocks attached to this interrupt level */

		gpe_block = gpe_xrupt_info->gpe_block_list_head;
		while (gpe_block) {
			walk_info.gpe_block = gpe_block;
			walk_info.gpe_device = gpe_block->node;

			status = acpi_ns_walk_namespace(ACPI_TYPE_METHOD,
							walk_info.gpe_device,
							ACPI_UINT32_MAX,
							ACPI_NS_WALK_NO_UNLOCK,
							acpi_ev_match_gpe_method,
							NULL, &walk_info, NULL);
			if (ACPI_FAILURE(status)) {
				ACPI_EXCEPTION((AE_INFO, status,
						"While decoding _Lxx/_Exx methods"));
			}

			gpe_block = gpe_block->next;
		}

		gpe_xrupt_info = gpe_xrupt_info->next;
	}

	if (walk_info.count) {
		ACPI_INFO(("Enabled %u new GPEs", walk_info.count));
	}

	(void)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	return;
}