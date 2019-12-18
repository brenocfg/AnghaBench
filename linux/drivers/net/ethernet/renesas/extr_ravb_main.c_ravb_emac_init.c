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
struct net_device {int mtu; int features; int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int ECMR_DM ; 
 int ECMR_RCSC ; 
 int ECMR_RE ; 
 int ECMR_TE ; 
 int ECMR_ZPF ; 
 int /*<<< orphan*/  ECSIPR ; 
 int ECSIPR_ICDIP ; 
 int ECSIPR_LCHNGIP ; 
 int ECSIPR_MPDIP ; 
 int /*<<< orphan*/  ECSR ; 
 int ECSR_ICD ; 
 int ECSR_MPD ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  MAHR ; 
 int /*<<< orphan*/  MALR ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  RFLR ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  ravb_set_rate (struct net_device*) ; 
 int /*<<< orphan*/  ravb_write (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ravb_emac_init(struct net_device *ndev)
{
	/* Receive frame limit set register */
	ravb_write(ndev, ndev->mtu + ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN, RFLR);

	/* EMAC Mode: PAUSE prohibition; Duplex; RX Checksum; TX; RX */
	ravb_write(ndev, ECMR_ZPF | ECMR_DM |
		   (ndev->features & NETIF_F_RXCSUM ? ECMR_RCSC : 0) |
		   ECMR_TE | ECMR_RE, ECMR);

	ravb_set_rate(ndev);

	/* Set MAC address */
	ravb_write(ndev,
		   (ndev->dev_addr[0] << 24) | (ndev->dev_addr[1] << 16) |
		   (ndev->dev_addr[2] << 8)  | (ndev->dev_addr[3]), MAHR);
	ravb_write(ndev,
		   (ndev->dev_addr[4] << 8)  | (ndev->dev_addr[5]), MALR);

	/* E-MAC status register clear */
	ravb_write(ndev, ECSR_ICD | ECSR_MPD, ECSR);

	/* E-MAC interrupt enable register */
	ravb_write(ndev, ECSIPR_ICDIP | ECSIPR_MPDIP | ECSIPR_LCHNGIP, ECSIPR);
}