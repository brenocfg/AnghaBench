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
struct input_dev {int dummy; } ;
struct hidpp_device {int dummy; } ;
struct hid_input {struct input_dev* input; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hidpp_populate_input (struct hidpp_device*,struct input_dev*) ; 

__attribute__((used)) static int hidpp_input_configured(struct hid_device *hdev,
				struct hid_input *hidinput)
{
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	struct input_dev *input = hidinput->input;

	if (!hidpp)
		return 0;

	hidpp_populate_input(hidpp, input);

	return 0;
}