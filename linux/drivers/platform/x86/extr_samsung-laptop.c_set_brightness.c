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
typedef  scalar_t__ u8 ;
struct samsung_laptop {scalar_t__ has_stepping_quirk; struct sabi_config* config; } ;
struct sabi_commands {int /*<<< orphan*/  set_brightness; } ;
struct sabi_config {scalar_t__ min_brightness; struct sabi_commands commands; } ;

/* Variables and functions */
 scalar_t__ read_brightness (struct samsung_laptop*) ; 
 int /*<<< orphan*/  sabi_set_commandb (struct samsung_laptop*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void set_brightness(struct samsung_laptop *samsung, u8 user_brightness)
{
	const struct sabi_config *config = samsung->config;
	const struct sabi_commands *commands = &samsung->config->commands;
	u8 user_level = user_brightness + config->min_brightness;

	if (samsung->has_stepping_quirk && user_level != 0) {
		/*
		 * short circuit if the specified level is what's already set
		 * to prevent the screen from flickering needlessly
		 */
		if (user_brightness == read_brightness(samsung))
			return;

		sabi_set_commandb(samsung, commands->set_brightness, 0);
	}

	sabi_set_commandb(samsung, commands->set_brightness, user_level);
}