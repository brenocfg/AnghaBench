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
struct TYPE_3__ {void* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  macaddr; TYPE_1__ eeprom; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int MT_EE_MAC_ADDR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76x2_eeprom_get_macaddr(struct mt76x02_dev *dev)
{
	void *src = dev->mt76.eeprom.data + MT_EE_MAC_ADDR;

	memcpy(dev->mt76.macaddr, src, ETH_ALEN);
	return 0;
}