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
struct mt_device {int /*<<< orphan*/  mt_io_flags; } ;
struct mt_application {int quirks; scalar_t__ left_button_state; scalar_t__ num_received; scalar_t__ timestamp; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  MSC_TIMESTAMP ; 
 int /*<<< orphan*/  MT_IO_FLAGS_ACTIVE_SLOTS ; 
 int /*<<< orphan*/  MT_IO_FLAGS_PENDING_SLOTS ; 
 int MT_QUIRK_WIN8_PTP_BUTTONS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_mt_sync_frame (struct input_dev*) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mt_release_pending_palms (struct mt_device*,struct mt_application*,struct input_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt_sync_frame(struct mt_device *td, struct mt_application *app,
			  struct input_dev *input)
{
	if (app->quirks & MT_QUIRK_WIN8_PTP_BUTTONS)
		input_event(input, EV_KEY, BTN_LEFT, app->left_button_state);

	input_mt_sync_frame(input);
	input_event(input, EV_MSC, MSC_TIMESTAMP, app->timestamp);
	input_sync(input);

	mt_release_pending_palms(td, app, input);

	app->num_received = 0;
	app->left_button_state = 0;

	if (test_bit(MT_IO_FLAGS_ACTIVE_SLOTS, &td->mt_io_flags))
		set_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags);
	else
		clear_bit(MT_IO_FLAGS_PENDING_SLOTS, &td->mt_io_flags);
	clear_bit(MT_IO_FLAGS_ACTIVE_SLOTS, &td->mt_io_flags);
}