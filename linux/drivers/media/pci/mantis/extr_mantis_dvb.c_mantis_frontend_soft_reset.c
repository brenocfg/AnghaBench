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
struct mantis_pci {struct mantis_hwconfig* hwconfig; } ;
struct mantis_hwconfig {int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mantis_gpio_set_bits (struct mantis_pci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

void mantis_frontend_soft_reset(struct mantis_pci *mantis)
{
	struct mantis_hwconfig *config = mantis->hwconfig;

	dprintk(MANTIS_DEBUG, 1, "Frontend RESET");
	mantis_gpio_set_bits(mantis, config->reset, 0);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 0);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 1);
	msleep(100);
	mantis_gpio_set_bits(mantis, config->reset, 1);
	msleep(100);

	return;
}