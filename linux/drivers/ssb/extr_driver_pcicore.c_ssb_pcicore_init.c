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
struct ssb_pcicore {scalar_t__ hostmode; struct ssb_device* dev; } ;
struct ssb_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ pcicore_is_in_hostmode (struct ssb_pcicore*) ; 
 int /*<<< orphan*/  ssb_device_enable (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_device_is_enabled (struct ssb_device*) ; 
 int /*<<< orphan*/  ssb_pcicore_init_clientmode (struct ssb_pcicore*) ; 
 int /*<<< orphan*/  ssb_pcicore_init_hostmode (struct ssb_pcicore*) ; 

void ssb_pcicore_init(struct ssb_pcicore *pc)
{
	struct ssb_device *dev = pc->dev;

	if (!dev)
		return;
	if (!ssb_device_is_enabled(dev))
		ssb_device_enable(dev, 0);

#ifdef CONFIG_SSB_PCICORE_HOSTMODE
	pc->hostmode = pcicore_is_in_hostmode(pc);
	if (pc->hostmode)
		ssb_pcicore_init_hostmode(pc);
#endif /* CONFIG_SSB_PCICORE_HOSTMODE */
	if (!pc->hostmode)
		ssb_pcicore_init_clientmode(pc);
}