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
typedef  int u8 ;
struct usbnet {TYPE_1__* net; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  SFR_RXCOE_CTL ; 
 int SFR_RXCOE_IP ; 
 int SFR_RXCOE_TCP ; 
 int SFR_RXCOE_TCPV6 ; 
 int SFR_RXCOE_UDP ; 
 int SFR_RXCOE_UDPV6 ; 
 int /*<<< orphan*/  SFR_TXCOE_CTL ; 
 int SFR_TXCOE_IP ; 
 int SFR_TXCOE_TCP ; 
 int SFR_TXCOE_TCPV6 ; 
 int SFR_TXCOE_UDP ; 
 int SFR_TXCOE_UDPV6 ; 
 int /*<<< orphan*/  aqc111_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 

__attribute__((used)) static void aqc111_configure_csum_offload(struct usbnet *dev)
{
	u8 reg8 = 0;

	if (dev->net->features & NETIF_F_RXCSUM) {
		reg8 |= SFR_RXCOE_IP | SFR_RXCOE_TCP | SFR_RXCOE_UDP |
			SFR_RXCOE_TCPV6 | SFR_RXCOE_UDPV6;
	}
	aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_RXCOE_CTL, 1, 1, &reg8);

	reg8 = 0;
	if (dev->net->features & NETIF_F_IP_CSUM)
		reg8 |= SFR_TXCOE_IP | SFR_TXCOE_TCP | SFR_TXCOE_UDP;

	if (dev->net->features & NETIF_F_IPV6_CSUM)
		reg8 |= SFR_TXCOE_TCPV6 | SFR_TXCOE_UDPV6;

	aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL, 1, 1, &reg8);
}