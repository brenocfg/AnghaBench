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
typedef  int u32 ;
struct ssb_chipcommon {TYPE_1__* dev; } ;
struct ssb_bus {int chip_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct ssb_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

u32 ssb_pmu_get_controlclock(struct ssb_chipcommon *cc)
{
	struct ssb_bus *bus = cc->dev->bus;

	switch (bus->chip_id) {
	case 0x5354:
		return 120000000;
	default:
		dev_err(cc->dev->dev, "ERROR: PMU controlclock unknown for device %04X\n",
			bus->chip_id);
		return 0;
	}
}