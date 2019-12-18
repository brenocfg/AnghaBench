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
struct platform_device {int dummy; } ;
struct pcmcia_device {struct platform_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static void softingcs_remove(struct pcmcia_device *pcmcia)
{
	struct platform_device *pdev = pcmcia->priv;

	/* free bits */
	platform_device_unregister(pdev);
	/* release pcmcia stuff */
	pcmcia_disable_device(pcmcia);
}