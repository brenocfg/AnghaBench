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
struct ahd_phase_table_entry {int phase; } ;

/* Variables and functions */
 struct ahd_phase_table_entry* ahd_phase_table ; 
 size_t num_phases ; 

__attribute__((used)) static const struct ahd_phase_table_entry*
ahd_lookup_phase_entry(int phase)
{
	const struct ahd_phase_table_entry *entry;
	const struct ahd_phase_table_entry *last_entry;

	/*
	 * num_phases doesn't include the default entry which
	 * will be returned if the phase doesn't match.
	 */
	last_entry = &ahd_phase_table[num_phases];
	for (entry = ahd_phase_table; entry < last_entry; entry++) {
		if (phase == entry->phase)
			break;
	}
	return (entry);
}