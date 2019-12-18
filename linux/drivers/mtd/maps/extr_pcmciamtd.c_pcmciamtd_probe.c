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
struct pcmciamtd_dev {struct pcmcia_device* p_dev; } ;
struct pcmcia_device {struct pcmciamtd_dev* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pcmciamtd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pcmciamtd_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct pcmciamtd_dev*) ; 

__attribute__((used)) static int pcmciamtd_probe(struct pcmcia_device *link)
{
	struct pcmciamtd_dev *dev;

	/* Create new memory card device */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) return -ENOMEM;
	pr_debug("dev=0x%p\n", dev);

	dev->p_dev = link;
	link->priv = dev;

	return pcmciamtd_config(link);
}