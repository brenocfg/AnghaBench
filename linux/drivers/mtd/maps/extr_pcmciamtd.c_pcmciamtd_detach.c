#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcmciamtd_dev {TYPE_2__* mtd_info; TYPE_1__* p_dev; } ;
struct pcmcia_device {struct pcmciamtd_dev* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  mtd_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  pcmciamtd_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct pcmcia_device*) ; 

__attribute__((used)) static void pcmciamtd_detach(struct pcmcia_device *link)
{
	struct pcmciamtd_dev *dev = link->priv;

	pr_debug("link=0x%p\n", link);

	if(dev->mtd_info) {
		mtd_device_unregister(dev->mtd_info);
		dev_info(&dev->p_dev->dev, "mtd%d: Removing\n",
			 dev->mtd_info->index);
		map_destroy(dev->mtd_info);
	}

	pcmciamtd_release(link);
}