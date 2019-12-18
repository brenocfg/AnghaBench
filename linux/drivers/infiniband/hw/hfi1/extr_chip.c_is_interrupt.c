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
struct is_table {unsigned int end; scalar_t__ start; int /*<<< orphan*/  (* is_int ) (struct hfi1_devdata*,scalar_t__) ;scalar_t__ is_name; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,unsigned int) ; 
 struct is_table* is_table ; 
 int /*<<< orphan*/  stub1 (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  trace_hfi1_interrupt (struct hfi1_devdata*,struct is_table const*,unsigned int) ; 

__attribute__((used)) static void is_interrupt(struct hfi1_devdata *dd, unsigned int source)
{
	const struct is_table *entry;

	/* avoids a double compare by walking the table in-order */
	for (entry = &is_table[0]; entry->is_name; entry++) {
		if (source <= entry->end) {
			trace_hfi1_interrupt(dd, entry, source);
			entry->is_int(dd, source - entry->start);
			return;
		}
	}
	/* fell off the end */
	dd_dev_err(dd, "invalid interrupt source %u\n", source);
}