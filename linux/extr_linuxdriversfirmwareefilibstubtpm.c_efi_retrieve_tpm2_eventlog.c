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
typedef  int /*<<< orphan*/  efi_system_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  efi_retrieve_tpm2_eventlog_1_2 (int /*<<< orphan*/ *) ; 

void efi_retrieve_tpm2_eventlog(efi_system_table_t *sys_table_arg)
{
	/* Only try to retrieve the logs in 1.2 format. */
	efi_retrieve_tpm2_eventlog_1_2(sys_table_arg);
}