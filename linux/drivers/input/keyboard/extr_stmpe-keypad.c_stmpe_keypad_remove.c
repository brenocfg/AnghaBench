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
struct stmpe_keypad {int /*<<< orphan*/  stmpe; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMPE_BLOCK_KEYPAD ; 
 struct stmpe_keypad* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stmpe_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmpe_keypad_remove(struct platform_device *pdev)
{
	struct stmpe_keypad *keypad = platform_get_drvdata(pdev);

	stmpe_disable(keypad->stmpe, STMPE_BLOCK_KEYPAD);

	return 0;
}