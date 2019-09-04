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
struct pcmcia_device {int config_flags; int config_index; int /*<<< orphan*/  config_regs; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  PRESENT_OPTION ; 
 int avmcs_config (struct pcmcia_device*) ; 

__attribute__((used)) static int avmcs_probe(struct pcmcia_device *p_dev)
{
	/* General socket configuration */
	p_dev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
	p_dev->config_index = 1;
	p_dev->config_regs = PRESENT_OPTION;

	return avmcs_config(p_dev);
}