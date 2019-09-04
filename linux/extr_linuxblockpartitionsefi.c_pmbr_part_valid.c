#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ os_type; int /*<<< orphan*/  starting_lba; } ;
typedef  TYPE_1__ gpt_mbr_record ;

/* Variables and functions */
 scalar_t__ EFI_PMBR_OSTYPE_EFI_GPT ; 
 int GPT_MBR_PROTECTIVE ; 
 scalar_t__ GPT_PRIMARY_PARTITION_TABLE_LBA ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pmbr_part_valid(gpt_mbr_record *part)
{
	if (part->os_type != EFI_PMBR_OSTYPE_EFI_GPT)
		goto invalid;

	/* set to 0x00000001 (i.e., the LBA of the GPT Partition Header) */
	if (le32_to_cpu(part->starting_lba) != GPT_PRIMARY_PARTITION_TABLE_LBA)
		goto invalid;

	return GPT_MBR_PROTECTIVE;
invalid:
	return 0;
}