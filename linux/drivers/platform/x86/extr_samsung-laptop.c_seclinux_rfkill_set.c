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
struct samsung_rfkill {struct samsung_laptop* samsung; } ;
struct samsung_laptop {TYPE_1__* config; } ;
struct sabi_commands {int /*<<< orphan*/  set_wireless_button; } ;
struct TYPE_2__ {struct sabi_commands commands; } ;

/* Variables and functions */
 int sabi_set_commandb (struct samsung_laptop*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int seclinux_rfkill_set(void *data, bool blocked)
{
	struct samsung_rfkill *srfkill = data;
	struct samsung_laptop *samsung = srfkill->samsung;
	const struct sabi_commands *commands = &samsung->config->commands;

	return sabi_set_commandb(samsung, commands->set_wireless_button,
				 !blocked);
}