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
struct pm {int* data; scalar_t__ packetsize; scalar_t__ idx; TYPE_1__* slots; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int active; int x; int y; } ;

/* Variables and functions */
 scalar_t__ pm_checkpacket (int*) ; 
 int /*<<< orphan*/  pm_mtevent (struct pm*,struct input_dev*) ; 

__attribute__((used)) static void pm_parse_3000(struct pm *pm)
{
	struct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0xce) == 0x40 && pm->packetsize == ++pm->idx) {
		if (pm_checkpacket(pm->data)) {
			int slotnum = pm->data[0] & 0x0f;
			pm->slots[slotnum].active = pm->data[0] & 0x30;
			pm->slots[slotnum].x = pm->data[2] * 256 + pm->data[1];
			pm->slots[slotnum].y = pm->data[4] * 256 + pm->data[3];
			pm_mtevent(pm, dev);
		}
		pm->idx = 0;
	}
}