#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mt_report_data {int is_mt_collection; int /*<<< orphan*/  list; int /*<<< orphan*/  application; struct hid_report* report; } ;
struct mt_device {int /*<<< orphan*/  reports; TYPE_1__* hdev; } ;
struct hid_report {int maxfield; struct hid_field** field; } ;
struct hid_field {int flags; int report_count; TYPE_2__* usage; } ;
struct TYPE_4__ {scalar_t__ hid; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HID_DG_CONTACTID ; 
 int HID_MAIN_ITEM_VARIABLE ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct mt_report_data*) ; 
 struct mt_report_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt_find_application (struct mt_device*,struct hid_report*) ; 

__attribute__((used)) static struct mt_report_data *mt_allocate_report_data(struct mt_device *td,
						      struct hid_report *report)
{
	struct mt_report_data *rdata;
	struct hid_field *field;
	int r, n;

	rdata = devm_kzalloc(&td->hdev->dev, sizeof(*rdata), GFP_KERNEL);
	if (!rdata)
		return NULL;

	rdata->report = report;
	rdata->application = mt_find_application(td, report);

	if (!rdata->application) {
		devm_kfree(&td->hdev->dev, rdata);
		return NULL;
	}

	for (r = 0; r < report->maxfield; r++) {
		field = report->field[r];

		if (!(HID_MAIN_ITEM_VARIABLE & field->flags))
			continue;

		for (n = 0; n < field->report_count; n++) {
			if (field->usage[n].hid == HID_DG_CONTACTID)
				rdata->is_mt_collection = true;
		}
	}

	list_add_tail(&rdata->list, &td->reports);

	return rdata;
}