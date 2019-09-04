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
struct pcmcia_device {int config_flags; int config_index; int /*<<< orphan*/  config_regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CONF_AUTO_SET_IO ; 
 int CONF_ENABLE_IRQ ; 
 int /*<<< orphan*/  PRESENT_OPTION ; 
 int avma1cs_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int avma1cs_probe(struct pcmcia_device *p_dev)
{
	dev_dbg(&p_dev->dev, "avma1cs_attach()\n");

	/* General socket configuration */
	p_dev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
	p_dev->config_index = 1;
	p_dev->config_regs = PRESENT_OPTION;

	return avma1cs_config(p_dev);
}