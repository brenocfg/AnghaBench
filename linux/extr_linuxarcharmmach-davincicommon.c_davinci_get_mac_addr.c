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
struct nvmem_device {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {TYPE_1__* emac_pdata; } ;
struct TYPE_3__ {char* mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NVMEM ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  IS_BUILTIN (int /*<<< orphan*/ ) ; 
 TYPE_2__ davinci_soc_info ; 
 scalar_t__ nvmem_device_read (struct nvmem_device*,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void davinci_get_mac_addr(struct nvmem_device *nvmem, void *context)
{
	char *mac_addr = davinci_soc_info.emac_pdata->mac_addr;
	off_t offset = (off_t)context;

	if (!IS_BUILTIN(CONFIG_NVMEM)) {
		pr_warn("Cannot read MAC addr from EEPROM without CONFIG_NVMEM\n");
		return;
	}

	/* Read MAC addr from EEPROM */
	if (nvmem_device_read(nvmem, offset, ETH_ALEN, mac_addr) == ETH_ALEN)
		pr_info("Read MAC addr from EEPROM: %pM\n", mac_addr);
}