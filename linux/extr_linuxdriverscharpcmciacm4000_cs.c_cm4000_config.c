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
struct pcmcia_device {int /*<<< orphan*/  config_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_AUTO_SET_IO ; 
 int ENODEV ; 
 int /*<<< orphan*/  cm4000_config_check ; 
 int /*<<< orphan*/  cm4000_release (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_enable_device (struct pcmcia_device*) ; 
 scalar_t__ pcmcia_loop_config (struct pcmcia_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm4000_config(struct pcmcia_device * link, int devno)
{
	link->config_flags |= CONF_AUTO_SET_IO;

	/* read the config-tuples */
	if (pcmcia_loop_config(link, cm4000_config_check, NULL))
		goto cs_release;

	if (pcmcia_enable_device(link))
		goto cs_release;

	return 0;

cs_release:
	cm4000_release(link);
	return -ENODEV;
}