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
typedef  unsigned int u8 ;
struct input_polled_dev {struct input_dev* input; struct buttons_dev* private; } ;
struct input_dev {int dummy; } ;
struct buttons_dev {scalar_t__* count; int /*<<< orphan*/ * keymap; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ BUTTONS_COUNT_THRESHOLD ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 unsigned int button_status () ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void handle_buttons(struct input_polled_dev *dev)
{
	struct buttons_dev *bdev = dev->private;
	struct input_dev *input = dev->input;
	u8 status;
	int i;

	status = button_status();

	for (i = 0; i < ARRAY_SIZE(bdev->keymap); i++) {
		if (status & (1U << i)) {
			if (++bdev->count[i] == BUTTONS_COUNT_THRESHOLD) {
				input_event(input, EV_MSC, MSC_SCAN, i);
				input_report_key(input, bdev->keymap[i], 1);
				input_sync(input);
			}
		} else {
			if (bdev->count[i] >= BUTTONS_COUNT_THRESHOLD) {
				input_event(input, EV_MSC, MSC_SCAN, i);
				input_report_key(input, bdev->keymap[i], 0);
				input_sync(input);
			}
			bdev->count[i] = 0;
		}
	}
}