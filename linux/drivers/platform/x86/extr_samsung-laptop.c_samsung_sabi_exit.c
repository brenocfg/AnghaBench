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
struct samsung_laptop {struct sabi_config* config; int /*<<< orphan*/ * f0000_segment; int /*<<< orphan*/ * sabi_iface; } ;
struct TYPE_2__ {int set_linux; } ;
struct sabi_config {TYPE_1__ commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sabi_set_commandb (struct samsung_laptop*,int,int) ; 

__attribute__((used)) static void samsung_sabi_exit(struct samsung_laptop *samsung)
{
	const struct sabi_config *config = samsung->config;

	/* Turn off "Linux" mode in the BIOS */
	if (config && config->commands.set_linux != 0xff)
		sabi_set_commandb(samsung, config->commands.set_linux, 0x80);

	if (samsung->sabi_iface) {
		iounmap(samsung->sabi_iface);
		samsung->sabi_iface = NULL;
	}
	if (samsung->f0000_segment) {
		iounmap(samsung->f0000_segment);
		samsung->f0000_segment = NULL;
	}

	samsung->config = NULL;
}