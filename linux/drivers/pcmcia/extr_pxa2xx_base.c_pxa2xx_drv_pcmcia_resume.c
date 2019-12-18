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
struct pcmcia_low_level {int dummy; } ;
struct device {scalar_t__ platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  pxa2xx_configure_sockets (struct device*,struct pcmcia_low_level*) ; 

__attribute__((used)) static int pxa2xx_drv_pcmcia_resume(struct device *dev)
{
	struct pcmcia_low_level *ops = (struct pcmcia_low_level *)dev->platform_data;

	pxa2xx_configure_sockets(dev, ops);
	return 0;
}