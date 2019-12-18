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
struct magicmouse_sc {int /*<<< orphan*/ * input; } ;
struct hid_input {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 struct magicmouse_sc* hid_get_drvdata (struct hid_device*) ; 
 int magicmouse_setup_input (int /*<<< orphan*/ *,struct hid_device*) ; 

__attribute__((used)) static int magicmouse_input_configured(struct hid_device *hdev,
		struct hid_input *hi)

{
	struct magicmouse_sc *msc = hid_get_drvdata(hdev);
	int ret;

	ret = magicmouse_setup_input(msc->input, hdev);
	if (ret) {
		hid_err(hdev, "magicmouse setup input failed (%d)\n", ret);
		/* clean msc->input to notify probe() of the failure */
		msc->input = NULL;
		return ret;
	}

	return 0;
}