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
 int N_SONY_RFKILL ; 
 int /*<<< orphan*/  rfkill_destroy (scalar_t__) ; 
 int /*<<< orphan*/  rfkill_unregister (scalar_t__) ; 
 scalar_t__* sony_rfkill_devices ; 

__attribute__((used)) static void sony_nc_rfkill_cleanup(void)
{
	int i;

	for (i = 0; i < N_SONY_RFKILL; i++) {
		if (sony_rfkill_devices[i]) {
			rfkill_unregister(sony_rfkill_devices[i]);
			rfkill_destroy(sony_rfkill_devices[i]);
		}
	}
}