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
struct samsung_laptop {struct sabi_config* config; } ;
struct sabi_data {int* data; } ;
struct sabi_commands {int /*<<< orphan*/  get_brightness; } ;
struct sabi_config {int min_brightness; struct sabi_commands commands; } ;

/* Variables and functions */
 int sabi_command (struct samsung_laptop*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sabi_data*) ; 

__attribute__((used)) static int read_brightness(struct samsung_laptop *samsung)
{
	const struct sabi_config *config = samsung->config;
	const struct sabi_commands *commands = &samsung->config->commands;
	struct sabi_data sretval;
	int user_brightness = 0;
	int retval;

	retval = sabi_command(samsung, commands->get_brightness,
			      NULL, &sretval);
	if (retval)
		return retval;

	user_brightness = sretval.data[0];
	if (user_brightness > config->min_brightness)
		user_brightness -= config->min_brightness;
	else
		user_brightness = 0;

	return user_brightness;
}