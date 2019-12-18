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
struct sabi_data {int* data; } ;
struct sabi_commands {int get_lid_handling; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {struct sabi_commands commands; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  memset (struct sabi_data*,int /*<<< orphan*/ ,int) ; 
 int sabi_command (struct samsung_laptop*,int,struct sabi_data*,struct sabi_data*) ; 

__attribute__((used)) static int read_lid_handling(struct samsung_laptop *samsung)
{
	const struct sabi_commands *commands = &samsung->config->commands;
	struct sabi_data data;
	int retval;

	if (commands->get_lid_handling == 0xFFFF)
		return -ENODEV;

	memset(&data, 0, sizeof(data));
	retval = sabi_command(samsung, commands->get_lid_handling,
			      &data, &data);

	if (retval)
		return retval;

	return data.data[0] & 0x1;
}