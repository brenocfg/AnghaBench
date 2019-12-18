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
struct intel_guc_client {int /*<<< orphan*/  priority; int /*<<< orphan*/  stage_id; } ;
struct guc_process_desc {int /*<<< orphan*/  priority; int /*<<< orphan*/  wq_status; int /*<<< orphan*/  wq_size_bytes; int /*<<< orphan*/  stage_id; scalar_t__ db_base_addr; scalar_t__ wq_base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_WQ_SIZE ; 
 int /*<<< orphan*/  WQ_STATUS_ACTIVE ; 
 int /*<<< orphan*/  __get_process_desc (struct intel_guc_client*) ; 
 struct guc_process_desc* memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void guc_proc_desc_init(struct intel_guc_client *client)
{
	struct guc_process_desc *desc;

	desc = memset(__get_process_desc(client), 0, sizeof(*desc));

	/*
	 * XXX: pDoorbell and WQVBaseAddress are pointers in process address
	 * space for ring3 clients (set them as in mmap_ioctl) or kernel
	 * space for kernel clients (map on demand instead? May make debug
	 * easier to have it mapped).
	 */
	desc->wq_base_addr = 0;
	desc->db_base_addr = 0;

	desc->stage_id = client->stage_id;
	desc->wq_size_bytes = GUC_WQ_SIZE;
	desc->wq_status = WQ_STATUS_ACTIVE;
	desc->priority = client->priority;
}