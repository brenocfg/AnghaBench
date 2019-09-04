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
struct max7359_keypad {int /*<<< orphan*/  client; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct max7359_keypad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  max7359_take_catnap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max7359_open(struct input_dev *dev)
{
	struct max7359_keypad *keypad = input_get_drvdata(dev);

	max7359_take_catnap(keypad->client);

	return 0;
}