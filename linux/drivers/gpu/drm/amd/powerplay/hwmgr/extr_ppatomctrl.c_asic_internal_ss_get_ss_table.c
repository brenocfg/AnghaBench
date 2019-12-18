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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  ATOM_ASIC_INTERNAL_SS_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_InternalSS_Info ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smu_atom_get_data_table (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ATOM_ASIC_INTERNAL_SS_INFO *asic_internal_ss_get_ss_table(void *device)
{
	ATOM_ASIC_INTERNAL_SS_INFO *table = NULL;
	u8 frev, crev;
	u16 size;

	table = (ATOM_ASIC_INTERNAL_SS_INFO *)
		smu_atom_get_data_table(device,
			GetIndexIntoMasterTable(DATA, ASIC_InternalSS_Info),
			&size, &frev, &crev);

	return table;
}