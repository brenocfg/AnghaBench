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

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_hid_destroy_emumouse () ; 
 int /*<<< orphan*/  mac_hid_emumouse_handler ; 

__attribute__((used)) static void mac_hid_stop_emulation(void)
{
	input_unregister_handler(&mac_hid_emumouse_handler);
	mac_hid_destroy_emumouse();
}