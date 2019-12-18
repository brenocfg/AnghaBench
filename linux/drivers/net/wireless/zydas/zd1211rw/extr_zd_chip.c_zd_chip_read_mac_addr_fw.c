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
typedef  int /*<<< orphan*/  u8 ;
struct zd_chip {int /*<<< orphan*/  usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_MAC_ADDR_P1 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_usb_read_fw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int zd_chip_read_mac_addr_fw(struct zd_chip *chip, u8 *addr)
{
	dev_dbg_f(zd_chip_dev(chip), "\n");
	return zd_usb_read_fw(&chip->usb, E2P_MAC_ADDR_P1, addr,
		ETH_ALEN);
}