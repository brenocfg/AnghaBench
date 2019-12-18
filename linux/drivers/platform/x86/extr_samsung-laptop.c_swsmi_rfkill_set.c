#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct samsung_rfkill {scalar_t__ type; struct samsung_laptop* samsung; } ;
struct samsung_laptop {TYPE_1__* config; } ;
struct sabi_data {int* data; } ;
struct sabi_commands {int /*<<< orphan*/  set_wireless_status; } ;
struct TYPE_2__ {struct sabi_commands commands; } ;

/* Variables and functions */
 scalar_t__ RFKILL_TYPE_BLUETOOTH ; 
 scalar_t__ RFKILL_TYPE_WLAN ; 
 size_t WL_STATUS_BT ; 
 size_t WL_STATUS_WLAN ; 
 int sabi_command (struct samsung_laptop*,int /*<<< orphan*/ ,struct sabi_data*,struct sabi_data*) ; 
 int swsmi_wireless_status (struct samsung_laptop*,struct sabi_data*) ; 

__attribute__((used)) static int swsmi_rfkill_set(void *priv, bool blocked)
{
	struct samsung_rfkill *srfkill = priv;
	struct samsung_laptop *samsung = srfkill->samsung;
	const struct sabi_commands *commands = &samsung->config->commands;
	struct sabi_data data;
	int ret, i;

	ret = swsmi_wireless_status(samsung, &data);
	if (ret)
		return ret;

	/* Don't set the state for non-present devices */
	for (i = 0; i < 4; i++)
		if (data.data[i] == 0x02)
			data.data[1] = 0;

	if (srfkill->type == RFKILL_TYPE_WLAN)
		data.data[WL_STATUS_WLAN] = !blocked;
	else if (srfkill->type == RFKILL_TYPE_BLUETOOTH)
		data.data[WL_STATUS_BT] = !blocked;

	return sabi_command(samsung, commands->set_wireless_status,
			    &data, &data);
}