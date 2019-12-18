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
struct b43_wldev {TYPE_1__* dev; } ;
struct TYPE_2__ {int core_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_MMIO_XMITSTAT_0 ; 
 int /*<<< orphan*/  B43_MMIO_XMITSTAT_1 ; 
 int b43_read32 (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drain_txstatus_queue(struct b43_wldev *dev)
{
	u32 dummy;

	if (dev->dev->core_rev < 5)
		return;
	/* Read all entries from the microcode TXstatus FIFO
	 * and throw them away.
	 */
	while (1) {
		dummy = b43_read32(dev, B43_MMIO_XMITSTAT_0);
		if (!(dummy & 0x00000001))
			break;
		dummy = b43_read32(dev, B43_MMIO_XMITSTAT_1);
	}
}