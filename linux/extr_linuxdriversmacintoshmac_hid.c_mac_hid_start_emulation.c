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
 int input_register_handler (int /*<<< orphan*/ *) ; 
 int mac_hid_create_emumouse () ; 
 int /*<<< orphan*/  mac_hid_destroy_emumouse () ; 
 int /*<<< orphan*/  mac_hid_emumouse_handler ; 

__attribute__((used)) static int mac_hid_start_emulation(void)
{
	int err;

	err = mac_hid_create_emumouse();
	if (err)
		return err;

	err = input_register_handler(&mac_hid_emumouse_handler);
	if (err) {
		mac_hid_destroy_emumouse();
		return err;
	}

	return 0;
}