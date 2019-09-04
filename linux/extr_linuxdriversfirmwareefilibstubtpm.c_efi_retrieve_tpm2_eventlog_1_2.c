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
struct tcpa_event {int event_size; } ;
struct linux_efi_tpm_eventlog {size_t size; int /*<<< orphan*/  log; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  size_t efi_physical_addr_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_LOADER_DATA ; 
 scalar_t__ EFI_SUCCESS ; 
 int /*<<< orphan*/  EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 ; 
 int /*<<< orphan*/  EFI_TCG2_PROTOCOL_GUID ; 
 int /*<<< orphan*/  LINUX_EFI_TPM_EVENT_LOG_GUID ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,struct linux_efi_tpm_eventlog*,...) ; 
 scalar_t__ efi_call_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efi_printk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  efi_tcg2_protocol ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  get_event_log ; 
 int /*<<< orphan*/  install_configuration_table ; 
 int /*<<< orphan*/  locate_protocol ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memset (struct linux_efi_tpm_eventlog*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void efi_retrieve_tpm2_eventlog_1_2(efi_system_table_t *sys_table_arg)
{
	efi_guid_t tcg2_guid = EFI_TCG2_PROTOCOL_GUID;
	efi_guid_t linux_eventlog_guid = LINUX_EFI_TPM_EVENT_LOG_GUID;
	efi_status_t status;
	efi_physical_addr_t log_location = 0, log_last_entry = 0;
	struct linux_efi_tpm_eventlog *log_tbl = NULL;
	unsigned long first_entry_addr, last_entry_addr;
	size_t log_size, last_entry_size;
	efi_bool_t truncated;
	void *tcg2_protocol = NULL;

	status = efi_call_early(locate_protocol, &tcg2_guid, NULL,
				&tcg2_protocol);
	if (status != EFI_SUCCESS)
		return;

	status = efi_call_proto(efi_tcg2_protocol, get_event_log, tcg2_protocol,
				EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2,
				&log_location, &log_last_entry, &truncated);
	if (status != EFI_SUCCESS)
		return;

	if (!log_location)
		return;
	first_entry_addr = (unsigned long) log_location;

	/*
	 * We populate the EFI table even if the logs are empty.
	 */
	if (!log_last_entry) {
		log_size = 0;
	} else {
		last_entry_addr = (unsigned long) log_last_entry;
		/*
		 * get_event_log only returns the address of the last entry.
		 * We need to calculate its size to deduce the full size of
		 * the logs.
		 */
		last_entry_size = sizeof(struct tcpa_event) +
			((struct tcpa_event *) last_entry_addr)->event_size;
		log_size = log_last_entry - log_location + last_entry_size;
	}

	/* Allocate space for the logs and copy them. */
	status = efi_call_early(allocate_pool, EFI_LOADER_DATA,
				sizeof(*log_tbl) + log_size,
				(void **) &log_tbl);

	if (status != EFI_SUCCESS) {
		efi_printk(sys_table_arg,
			   "Unable to allocate memory for event log\n");
		return;
	}

	memset(log_tbl, 0, sizeof(*log_tbl) + log_size);
	log_tbl->size = log_size;
	log_tbl->version = EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2;
	memcpy(log_tbl->log, (void *) first_entry_addr, log_size);

	status = efi_call_early(install_configuration_table,
				&linux_eventlog_guid, log_tbl);
	if (status != EFI_SUCCESS)
		goto err_free;
	return;

err_free:
	efi_call_early(free_pool, log_tbl);
}