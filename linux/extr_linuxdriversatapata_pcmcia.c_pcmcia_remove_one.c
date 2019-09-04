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
struct pcmcia_device {struct ata_host* priv; } ;
struct ata_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void pcmcia_remove_one(struct pcmcia_device *pdev)
{
	struct ata_host *host = pdev->priv;

	if (host)
		ata_host_detach(host);

	pcmcia_disable_device(pdev);
}