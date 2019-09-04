#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct e820_entry {int dummy; } ;
struct boot_params {unsigned int e820_entries; int /*<<< orphan*/  e820_table; } ;
struct TYPE_2__ {unsigned int nr_entries; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 unsigned int E820_MAX_ENTRIES_ZEROPAGE ; 
 TYPE_1__* e820_table_kexec ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int setup_e820_entries(struct boot_params *params)
{
	unsigned int nr_e820_entries;

	nr_e820_entries = e820_table_kexec->nr_entries;

	/* TODO: Pass entries more than E820_MAX_ENTRIES_ZEROPAGE in bootparams setup data */
	if (nr_e820_entries > E820_MAX_ENTRIES_ZEROPAGE)
		nr_e820_entries = E820_MAX_ENTRIES_ZEROPAGE;

	params->e820_entries = nr_e820_entries;
	memcpy(&params->e820_table, &e820_table_kexec->entries, nr_e820_entries*sizeof(struct e820_entry));

	return 0;
}