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
struct platform_device {int dummy; } ;
struct matrix_keypad {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct matrix_keypad*) ; 
 int /*<<< orphan*/  matrix_keypad_free_gpio (struct matrix_keypad*) ; 
 struct matrix_keypad* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int matrix_keypad_remove(struct platform_device *pdev)
{
	struct matrix_keypad *keypad = platform_get_drvdata(pdev);

	matrix_keypad_free_gpio(keypad);
	input_unregister_device(keypad->input_dev);
	kfree(keypad);

	return 0;
}