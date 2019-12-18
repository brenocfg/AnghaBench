#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int revision; } ;
struct ssb_device {TYPE_2__* bus; TYPE_1__ id; } ;
struct TYPE_4__ {int chip_id; } ;

/* Variables and functions */
 int ssb_read32 (struct ssb_device*,int) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int,int) ; 

__attribute__((used)) static void ssb_hcd_5354wa(struct ssb_device *dev)
{
#ifdef CONFIG_SSB_DRIVER_MIPS
	/* Work around for 5354 failures */
	if (dev->id.revision == 2 && dev->bus->chip_id == 0x5354) {
		/* Change syn01 reg */
		ssb_write32(dev, 0x894, 0x00fe00fe);

		/* Change syn03 reg */
		ssb_write32(dev, 0x89c, ssb_read32(dev, 0x89c) | 0x1);
	}
#endif
}