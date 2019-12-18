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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  A1655_WIFI_COMMAND ; 
 int /*<<< orphan*/  A1655_WIFI_OFF ; 
 int /*<<< orphan*/  A1655_WIFI_ON ; 
 int i8042_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8042_lock_chip () ; 
 int /*<<< orphan*/  i8042_unlock_chip () ; 

__attribute__((used)) static int amilo_a1655_rfkill_set_block(void *data, bool blocked)
{
	u8 param = blocked ? A1655_WIFI_OFF : A1655_WIFI_ON;
	int rc;

	i8042_lock_chip();
	rc = i8042_command(&param, A1655_WIFI_COMMAND);
	i8042_unlock_chip();
	return rc;
}