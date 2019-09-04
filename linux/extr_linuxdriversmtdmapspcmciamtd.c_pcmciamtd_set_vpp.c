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
struct pcmciamtd_dev {int /*<<< orphan*/  vpp; struct pcmcia_device* p_dev; } ;
struct pcmcia_device {int dummy; } ;
struct map_info {scalar_t__ map_priv_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmcia_fixup_vpp (struct pcmcia_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_vpp_lock ; 
 int pcmcia_vpp_refcnt ; 
 int /*<<< orphan*/  pr_debug (char*,struct pcmciamtd_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pcmciamtd_set_vpp(struct map_info *map, int on)
{
	struct pcmciamtd_dev *dev = (struct pcmciamtd_dev *)map->map_priv_1;
	struct pcmcia_device *link = dev->p_dev;
	unsigned long flags;

	pr_debug("dev = %p on = %d vpp = %d\n\n", dev, on, dev->vpp);
	spin_lock_irqsave(&pcmcia_vpp_lock, flags);
	if (on) {
		if (++pcmcia_vpp_refcnt == 1)   /* first nested 'on' */
			pcmcia_fixup_vpp(link, dev->vpp);
	} else {
		if (--pcmcia_vpp_refcnt == 0)   /* last nested 'off' */
			pcmcia_fixup_vpp(link, 0);
	}
	spin_unlock_irqrestore(&pcmcia_vpp_lock, flags);
}