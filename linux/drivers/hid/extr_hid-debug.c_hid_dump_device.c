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
struct seq_file {int dummy; } ;
struct list_head {struct list_head* next; } ;
struct hid_report_enum {struct list_head report_list; } ;
struct hid_report {unsigned int id; size_t type; unsigned int maxfield; int /*<<< orphan*/ * field; } ;
struct hid_device {struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 unsigned int HID_REPORT_TYPES ; 
 int /*<<< orphan*/  hid_dump_field (int /*<<< orphan*/ ,int,struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  tab (int,struct seq_file*) ; 

void hid_dump_device(struct hid_device *device, struct seq_file *f)
{
	struct hid_report_enum *report_enum;
	struct hid_report *report;
	struct list_head *list;
	unsigned i,k;
	static const char *table[] = {"INPUT", "OUTPUT", "FEATURE"};

	for (i = 0; i < HID_REPORT_TYPES; i++) {
		report_enum = device->report_enum + i;
		list = report_enum->report_list.next;
		while (list != &report_enum->report_list) {
			report = (struct hid_report *) list;
			tab(2, f);
			seq_printf(f, "%s", table[i]);
			if (report->id)
				seq_printf(f, "(%d)", report->id);
			seq_printf(f, "[%s]", table[report->type]);
			seq_printf(f, "\n");
			for (k = 0; k < report->maxfield; k++) {
				tab(4, f);
				seq_printf(f, "Field(%d)\n", k);
				hid_dump_field(report->field[k], 6, f);
			}
			list = list->next;
		}
	}
}