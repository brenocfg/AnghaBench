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
struct uclogic_drvdata {int /*<<< orphan*/  params; int /*<<< orphan*/  desc_ptr; int /*<<< orphan*/  inrange_timer; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct uclogic_drvdata* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uclogic_params_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uclogic_remove(struct hid_device *hdev)
{
	struct uclogic_drvdata *drvdata = hid_get_drvdata(hdev);

	del_timer_sync(&drvdata->inrange_timer);
	hid_hw_stop(hdev);
	kfree(drvdata->desc_ptr);
	uclogic_params_cleanup(&drvdata->params);
}