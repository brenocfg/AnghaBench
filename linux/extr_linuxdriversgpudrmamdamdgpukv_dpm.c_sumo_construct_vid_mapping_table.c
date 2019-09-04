#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct sumo_vid_mapping_table {size_t num_entries; TYPE_1__* entries; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ ulSupportedSCLK; size_t usVoltageIndex; scalar_t__ usVoltageID; } ;
struct TYPE_4__ {scalar_t__ vid_7bit; size_t vid_2bit; } ;
typedef  TYPE_2__ ATOM_AVAILABLE_SCLK_LIST ;

/* Variables and functions */
 size_t SUMO_MAX_HARDWARE_POWERLEVELS ; 
 size_t SUMO_MAX_NUMBER_VOLTAGES ; 

__attribute__((used)) static void sumo_construct_vid_mapping_table(struct amdgpu_device *adev,
					     struct sumo_vid_mapping_table *vid_mapping_table,
					     ATOM_AVAILABLE_SCLK_LIST *table)
{
	u32 i, j;

	for (i = 0; i < SUMO_MAX_HARDWARE_POWERLEVELS; i++) {
		if (table[i].ulSupportedSCLK != 0) {
			vid_mapping_table->entries[table[i].usVoltageIndex].vid_7bit =
				table[i].usVoltageID;
			vid_mapping_table->entries[table[i].usVoltageIndex].vid_2bit =
				table[i].usVoltageIndex;
		}
	}

	for (i = 0; i < SUMO_MAX_NUMBER_VOLTAGES; i++) {
		if (vid_mapping_table->entries[i].vid_7bit == 0) {
			for (j = i + 1; j < SUMO_MAX_NUMBER_VOLTAGES; j++) {
				if (vid_mapping_table->entries[j].vid_7bit != 0) {
					vid_mapping_table->entries[i] =
						vid_mapping_table->entries[j];
					vid_mapping_table->entries[j].vid_7bit = 0;
					break;
				}
			}

			if (j == SUMO_MAX_NUMBER_VOLTAGES)
				break;
		}
	}

	vid_mapping_table->num_entries = i;
}