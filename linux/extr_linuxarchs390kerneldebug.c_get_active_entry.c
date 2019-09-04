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
struct TYPE_3__ {size_t active_area; size_t* active_pages; int* active_entries; scalar_t__** areas; } ;
typedef  TYPE_1__ debug_info_t ;
typedef  int /*<<< orphan*/  debug_entry_t ;

/* Variables and functions */

__attribute__((used)) static inline debug_entry_t *get_active_entry(debug_info_t *id)
{
	return (debug_entry_t *) (((char *) id->areas[id->active_area]
				   [id->active_pages[id->active_area]]) +
				  id->active_entries[id->active_area]);
}