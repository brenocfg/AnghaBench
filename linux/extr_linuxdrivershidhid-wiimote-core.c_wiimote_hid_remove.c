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
struct wiimote_data {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 struct wiimote_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_info (struct hid_device*,char*) ; 
 int /*<<< orphan*/  wiimote_destroy (struct wiimote_data*) ; 

__attribute__((used)) static void wiimote_hid_remove(struct hid_device *hdev)
{
	struct wiimote_data *wdata = hid_get_drvdata(hdev);

	hid_info(hdev, "Device removed\n");
	wiimote_destroy(wdata);
}