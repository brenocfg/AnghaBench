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
typedef  int u32 ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MAHR ; 
 int /*<<< orphan*/  MALR ; 
 int /*<<< orphan*/  ether_addr_copy (int*,int /*<<< orphan*/  const*) ; 
 int ravb_read (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ravb_read_mac_address(struct net_device *ndev, const u8 *mac)
{
	if (!IS_ERR(mac)) {
		ether_addr_copy(ndev->dev_addr, mac);
	} else {
		u32 mahr = ravb_read(ndev, MAHR);
		u32 malr = ravb_read(ndev, MALR);

		ndev->dev_addr[0] = (mahr >> 24) & 0xFF;
		ndev->dev_addr[1] = (mahr >> 16) & 0xFF;
		ndev->dev_addr[2] = (mahr >>  8) & 0xFF;
		ndev->dev_addr[3] = (mahr >>  0) & 0xFF;
		ndev->dev_addr[4] = (malr >>  8) & 0xFF;
		ndev->dev_addr[5] = (malr >>  0) & 0xFF;
	}
}