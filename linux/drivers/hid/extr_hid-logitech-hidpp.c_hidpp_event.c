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
struct hidpp_scroll_counter {scalar_t__ wheel_multiplier; } ;
struct hidpp_device {int quirks; int /*<<< orphan*/ * input; struct hidpp_scroll_counter vertical_wheel_counter; } ;
struct hid_usage {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int HIDPP_QUIRK_HI_RES_SCROLL ; 
 struct hidpp_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  hidpp_scroll_counter_handle_scroll (int /*<<< orphan*/ *,struct hidpp_scroll_counter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidpp_event(struct hid_device *hdev, struct hid_field *field,
	struct hid_usage *usage, __s32 value)
{
	/* This function will only be called for scroll events, due to the
	 * restriction imposed in hidpp_usages.
	 */
	struct hidpp_device *hidpp = hid_get_drvdata(hdev);
	struct hidpp_scroll_counter *counter;

	if (!hidpp)
		return 0;

	counter = &hidpp->vertical_wheel_counter;
	/* A scroll event may occur before the multiplier has been retrieved or
	 * the input device set, or high-res scroll enabling may fail. In such
	 * cases we must return early (falling back to default behaviour) to
	 * avoid a crash in hidpp_scroll_counter_handle_scroll.
	 */
	if (!(hidpp->quirks & HIDPP_QUIRK_HI_RES_SCROLL) || value == 0
	    || hidpp->input == NULL || counter->wheel_multiplier == 0)
		return 0;

	hidpp_scroll_counter_handle_scroll(hidpp->input, counter, value);
	return 1;
}