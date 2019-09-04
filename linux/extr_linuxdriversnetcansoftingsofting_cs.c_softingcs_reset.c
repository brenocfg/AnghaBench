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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int) ; 
 int pcmcia_write_config_byte (struct pcmcia_device*,int,int) ; 
 struct pcmcia_device* to_pcmcia_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int softingcs_reset(struct platform_device *pdev, int v)
{
	struct pcmcia_device *pcmcia = to_pcmcia_dev(pdev->dev.parent);

	dev_dbg(&pdev->dev, "pcmcia config [2] %02x\n", v ? 0 : 0x20);
	return pcmcia_write_config_byte(pcmcia, 2, v ? 0 : 0x20);
}