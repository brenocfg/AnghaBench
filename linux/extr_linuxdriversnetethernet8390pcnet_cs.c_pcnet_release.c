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
struct pcnet_dev {int flags; int /*<<< orphan*/  base; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 struct pcnet_dev* PRIV (int /*<<< orphan*/ ) ; 
 int USE_SHMEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void pcnet_release(struct pcmcia_device *link)
{
	struct pcnet_dev *info = PRIV(link->priv);

	dev_dbg(&link->dev, "pcnet_release\n");

	if (info->flags & USE_SHMEM)
		iounmap(info->base);

	pcmcia_disable_device(link);
}