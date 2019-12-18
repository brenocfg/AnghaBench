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
typedef  int u8 ;
typedef  int u16 ;
struct realtek_smi {int /*<<< orphan*/  map; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  RTL8366RB_SMAR0 ; 
 int /*<<< orphan*/  RTL8366RB_SMAR1 ; 
 int /*<<< orphan*/  RTL8366RB_SMAR2 ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  eth_random_addr (int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtl8366rb_set_addr(struct realtek_smi *smi)
{
	u8 addr[ETH_ALEN];
	u16 val;
	int ret;

	eth_random_addr(addr);

	dev_info(smi->dev, "set MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
		 addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
	val = addr[0] << 8 | addr[1];
	ret = regmap_write(smi->map, RTL8366RB_SMAR0, val);
	if (ret)
		return ret;
	val = addr[2] << 8 | addr[3];
	ret = regmap_write(smi->map, RTL8366RB_SMAR1, val);
	if (ret)
		return ret;
	val = addr[4] << 8 | addr[5];
	ret = regmap_write(smi->map, RTL8366RB_SMAR2, val);
	if (ret)
		return ret;

	return 0;
}