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
struct steam_device {TYPE_1__* hdev; } ;
struct hid_device {struct steam_device* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_rsize; int /*<<< orphan*/  dev_rdesc; } ;

/* Variables and functions */
 int hid_parse_report (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int steam_client_ll_parse(struct hid_device *hdev)
{
	struct steam_device *steam = hdev->driver_data;

	return hid_parse_report(hdev, steam->hdev->dev_rdesc,
			steam->hdev->dev_rsize);
}