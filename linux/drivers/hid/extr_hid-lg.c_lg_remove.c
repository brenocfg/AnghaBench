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
struct lg_drv_data {int quirks; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int LG_FF4 ; 
 struct lg_drv_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (struct lg_drv_data*) ; 
 int /*<<< orphan*/  lg4ff_deinit (struct hid_device*) ; 

__attribute__((used)) static void lg_remove(struct hid_device *hdev)
{
	struct lg_drv_data *drv_data = hid_get_drvdata(hdev);
	if (drv_data->quirks & LG_FF4)
		lg4ff_deinit(hdev);
	hid_hw_stop(hdev);
	kfree(drv_data);
}