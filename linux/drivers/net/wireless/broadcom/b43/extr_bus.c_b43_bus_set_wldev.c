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
struct b43_bus_dev {int bus_type; int /*<<< orphan*/  sdev; int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
#define  B43_BUS_BCMA 129 
#define  B43_BUS_SSB 128 
 int /*<<< orphan*/  bcma_set_drvdata (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ssb_set_drvdata (int /*<<< orphan*/ ,void*) ; 

void b43_bus_set_wldev(struct b43_bus_dev *dev, void *wldev)
{
	switch (dev->bus_type) {
#ifdef CONFIG_B43_BCMA
	case B43_BUS_BCMA:
		bcma_set_drvdata(dev->bdev, wldev);
		break;
#endif
#ifdef CONFIG_B43_SSB
	case B43_BUS_SSB:
		ssb_set_drvdata(dev->sdev, wldev);
		break;
#endif
	}
}