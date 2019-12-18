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
struct ms_data {int quirks; int /*<<< orphan*/  ff_worker; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int MS_QUIRK_FF ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct ms_data* hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static void ms_remove_ff(struct hid_device *hdev)
{
	struct ms_data *ms = hid_get_drvdata(hdev);

	if (!(ms->quirks & MS_QUIRK_FF))
		return;

	cancel_work_sync(&ms->ff_worker);
}