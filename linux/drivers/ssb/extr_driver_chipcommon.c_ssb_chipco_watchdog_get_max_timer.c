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
typedef  int u32 ;
struct ssb_chipcommon {int capabilities; TYPE_2__* dev; } ;
struct TYPE_3__ {int revision; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int SSB_CHIPCO_CAP_PMU ; 

__attribute__((used)) static u32 ssb_chipco_watchdog_get_max_timer(struct ssb_chipcommon *cc)
{
	u32 nb;

	if (cc->capabilities & SSB_CHIPCO_CAP_PMU) {
		if (cc->dev->id.revision < 26)
			nb = 16;
		else
			nb = (cc->dev->id.revision >= 37) ? 32 : 24;
	} else {
		nb = 28;
	}
	if (nb == 32)
		return 0xffffffff;
	else
		return (1 << nb) - 1;
}