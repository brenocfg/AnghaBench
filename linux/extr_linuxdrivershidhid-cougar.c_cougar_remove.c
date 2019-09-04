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
struct hid_device {int dummy; } ;
struct cougar {scalar_t__ special_intf; TYPE_1__* shared; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 struct cougar* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_close (struct hid_device*) ; 
 int /*<<< orphan*/  hid_hw_stop (struct hid_device*) ; 

__attribute__((used)) static void cougar_remove(struct hid_device *hdev)
{
	struct cougar *cougar = hid_get_drvdata(hdev);

	if (cougar) {
		/* Stop the vendor intf to process more events */
		if (cougar->shared)
			cougar->shared->enabled = false;
		if (cougar->special_intf)
			hid_hw_close(hdev);
	}
	hid_hw_stop(hdev);
}