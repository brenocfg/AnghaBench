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
struct bcma_device {TYPE_2__* bus; } ;
struct TYPE_3__ {int id; } ;
struct TYPE_4__ {TYPE_1__ chipinfo; } ;

/* Variables and functions */
#define  BCMA_CHIP_ID_BCM4707 130 
#define  BCMA_CHIP_ID_BCM47094 129 
#define  BCMA_CHIP_ID_BCM53018 128 

__attribute__((used)) static inline bool bgmac_is_bcm4707_family(struct bcma_device *core)
{
	switch (core->bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4707:
	case BCMA_CHIP_ID_BCM47094:
	case BCMA_CHIP_ID_BCM53018:
		return true;
	default:
		return false;
	}
}