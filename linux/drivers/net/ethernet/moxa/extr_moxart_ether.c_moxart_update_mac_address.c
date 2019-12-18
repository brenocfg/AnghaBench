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
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 scalar_t__ REG_MAC_MS_ADDRESS ; 
 int /*<<< orphan*/  moxart_emac_write (struct net_device*,scalar_t__,int) ; 

__attribute__((used)) static void moxart_update_mac_address(struct net_device *ndev)
{
	moxart_emac_write(ndev, REG_MAC_MS_ADDRESS,
			  ((ndev->dev_addr[0] << 8) | (ndev->dev_addr[1])));
	moxart_emac_write(ndev, REG_MAC_MS_ADDRESS + 4,
			  ((ndev->dev_addr[2] << 24) |
			   (ndev->dev_addr[3] << 16) |
			   (ndev->dev_addr[4] << 8) |
			   (ndev->dev_addr[5])));
}