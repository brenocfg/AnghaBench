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
struct pxa27x_keypad_platform_data {int /*<<< orphan*/  clear_wakeup_event; } ;

/* Variables and functions */
 scalar_t__ cpu_is_pxa168 () ; 
 int /*<<< orphan*/  pxa168_clear_keypad_wakeup ; 
 int /*<<< orphan*/  pxa168_device_keypad ; 
 int pxa_register_device (int /*<<< orphan*/ *,struct pxa27x_keypad_platform_data*,int) ; 

__attribute__((used)) static inline int pxa168_add_keypad(struct pxa27x_keypad_platform_data *data)
{
	if (cpu_is_pxa168())
		data->clear_wakeup_event = pxa168_clear_keypad_wakeup;

	return pxa_register_device(&pxa168_device_keypad, data, sizeof(*data));
}