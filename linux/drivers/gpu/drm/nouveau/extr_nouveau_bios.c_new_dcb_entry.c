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
struct dcb_table {size_t entries; struct dcb_output* entry; } ;
struct dcb_output {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct dcb_output*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dcb_output *new_dcb_entry(struct dcb_table *dcb)
{
	struct dcb_output *entry = &dcb->entry[dcb->entries];

	memset(entry, 0, sizeof(struct dcb_output));
	entry->index = dcb->entries++;

	return entry;
}