#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct amdgpu_clock_voltage_dependency_table {int count; TYPE_3__* entries; } ;
struct amdgpu_clock_voltage_dependency_entry {int dummy; } ;
struct TYPE_7__ {int clk; int v; } ;
struct TYPE_6__ {int ucClockHigh; int /*<<< orphan*/  usVoltage; int /*<<< orphan*/  usClockLow; } ;
struct TYPE_5__ {int ucNumEntries; TYPE_2__* entries; } ;
typedef  TYPE_1__ ATOM_PPLIB_Clock_Voltage_Dependency_Table ;
typedef  TYPE_2__ ATOM_PPLIB_Clock_Voltage_Dependency_Record ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_parse_clk_voltage_dep_table(struct amdgpu_clock_voltage_dependency_table *amdgpu_table,
					      ATOM_PPLIB_Clock_Voltage_Dependency_Table *atom_table)
{
	u32 size = atom_table->ucNumEntries *
		sizeof(struct amdgpu_clock_voltage_dependency_entry);
	int i;
	ATOM_PPLIB_Clock_Voltage_Dependency_Record *entry;

	amdgpu_table->entries = kzalloc(size, GFP_KERNEL);
	if (!amdgpu_table->entries)
		return -ENOMEM;

	entry = &atom_table->entries[0];
	for (i = 0; i < atom_table->ucNumEntries; i++) {
		amdgpu_table->entries[i].clk = le16_to_cpu(entry->usClockLow) |
			(entry->ucClockHigh << 16);
		amdgpu_table->entries[i].v = le16_to_cpu(entry->usVoltage);
		entry = (ATOM_PPLIB_Clock_Voltage_Dependency_Record *)
			((u8 *)entry + sizeof(ATOM_PPLIB_Clock_Voltage_Dependency_Record));
	}
	amdgpu_table->count = atom_table->ucNumEntries;

	return 0;
}