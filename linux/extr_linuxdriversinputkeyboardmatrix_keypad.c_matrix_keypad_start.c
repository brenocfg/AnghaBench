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
struct matrix_keypad {int stopped; int /*<<< orphan*/  work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct matrix_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matrix_keypad_start(struct input_dev *dev)
{
	struct matrix_keypad *keypad = input_get_drvdata(dev);

	keypad->stopped = false;
	mb();

	/*
	 * Schedule an immediate key scan to capture current key state;
	 * columns will be activated and IRQs be enabled after the scan.
	 */
	schedule_delayed_work(&keypad->work, 0);

	return 0;
}