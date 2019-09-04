#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * pad_input; int /*<<< orphan*/ * touch_input; int /*<<< orphan*/ * pen_input; } ;
struct wacom {int resources; TYPE_1__ wacom_wac; struct hid_device* hdev; } ;
struct hid_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ *,struct wacom*) ; 

__attribute__((used)) static void wacom_release_resources(struct wacom *wacom)
{
	struct hid_device *hdev = wacom->hdev;

	if (!wacom->resources)
		return;

	devres_release_group(&hdev->dev, wacom);

	wacom->resources = false;

	wacom->wacom_wac.pen_input = NULL;
	wacom->wacom_wac.touch_input = NULL;
	wacom->wacom_wac.pad_input = NULL;
}