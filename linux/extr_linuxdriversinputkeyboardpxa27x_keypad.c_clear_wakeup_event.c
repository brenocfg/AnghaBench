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
struct pxa27x_keypad_platform_data {int /*<<< orphan*/  (* clear_wakeup_event ) () ;} ;
struct pxa27x_keypad {struct pxa27x_keypad_platform_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void clear_wakeup_event(struct pxa27x_keypad *keypad)
{
	const struct pxa27x_keypad_platform_data *pdata = keypad->pdata;

	if (pdata->clear_wakeup_event)
		(pdata->clear_wakeup_event)();
}