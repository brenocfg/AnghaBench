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
typedef  int /*<<< orphan*/  u8 ;
struct usbnet {TYPE_1__* net; } ;
struct TYPE_2__ {int /*<<< orphan*/  perm_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_FLASH_PARAMETERS ; 
 int ETH_ALEN ; 
 int aqc111_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aqc111_read_perm_mac(struct usbnet *dev)
{
	u8 buf[ETH_ALEN];
	int ret;

	ret = aqc111_read_cmd(dev, AQ_FLASH_PARAMETERS, 0, 0, ETH_ALEN, buf);
	if (ret < 0)
		goto out;

	ether_addr_copy(dev->net->perm_addr, buf);

	return 0;
out:
	return ret;
}