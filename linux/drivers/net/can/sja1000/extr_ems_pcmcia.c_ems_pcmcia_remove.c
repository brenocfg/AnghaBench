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
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ems_pcmcia_del_card (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void ems_pcmcia_remove(struct pcmcia_device *dev)
{
	ems_pcmcia_del_card(dev);
	pcmcia_disable_device(dev);
}