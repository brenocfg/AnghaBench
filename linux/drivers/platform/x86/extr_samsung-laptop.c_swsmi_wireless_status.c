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
struct samsung_laptop {TYPE_1__* config; } ;
struct sabi_data {int dummy; } ;
struct sabi_commands {int /*<<< orphan*/  get_wireless_status; } ;
struct TYPE_2__ {struct sabi_commands commands; } ;

/* Variables and functions */
 int sabi_command (struct samsung_laptop*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sabi_data*) ; 

__attribute__((used)) static int swsmi_wireless_status(struct samsung_laptop *samsung,
				 struct sabi_data *data)
{
	const struct sabi_commands *commands = &samsung->config->commands;

	return sabi_command(samsung, commands->get_wireless_status,
			    NULL, data);
}