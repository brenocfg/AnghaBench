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
struct usbnet {struct aqc111_data* driver_priv; } ;
struct net_device {int features; } ;
struct aqc111_data {int rx_checksum; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_ACCESS_MAC ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
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
 int SFR_TXCOE_TCP ; 
 int SFR_TXCOE_TCPV6 ; 
 int SFR_TXCOE_UDP ; 
 int SFR_TXCOE_UDPV6 ; 
 int SFR_VLAN_CONTROL_VFE ; 
 int SFR_VLAN_CONTROL_WE ; 
 int /*<<< orphan*/  SFR_VLAN_ID_ADDRESS ; 
 int /*<<< orphan*/  SFR_VLAN_ID_CONTROL ; 
 int /*<<< orphan*/  SFR_VLAN_ID_DATA0 ; 
 int /*<<< orphan*/  aqc111_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  aqc111_write16_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  aqc111_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 struct usbnet* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int aqc111_set_features(struct net_device *net,
			       netdev_features_t features)
{
	struct usbnet *dev = netdev_priv(net);
	struct aqc111_data *aqc111_data = dev->driver_priv;
	netdev_features_t changed = net->features ^ features;
	u16 reg16 = 0;
	u8 reg8 = 0;

	if (changed & NETIF_F_IP_CSUM) {
		aqc111_read_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL, 1, 1, &reg8);
		reg8 ^= SFR_TXCOE_TCP | SFR_TXCOE_UDP;
		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL,
				 1, 1, &reg8);
	}

	if (changed & NETIF_F_IPV6_CSUM) {
		aqc111_read_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL, 1, 1, &reg8);
		reg8 ^= SFR_TXCOE_TCPV6 | SFR_TXCOE_UDPV6;
		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_TXCOE_CTL,
				 1, 1, &reg8);
	}

	if (changed & NETIF_F_RXCSUM) {
		aqc111_read_cmd(dev, AQ_ACCESS_MAC, SFR_RXCOE_CTL, 1, 1, &reg8);
		if (features & NETIF_F_RXCSUM) {
			aqc111_data->rx_checksum = 1;
			reg8 &= ~(SFR_RXCOE_IP | SFR_RXCOE_TCP | SFR_RXCOE_UDP |
				  SFR_RXCOE_TCPV6 | SFR_RXCOE_UDPV6);
		} else {
			aqc111_data->rx_checksum = 0;
			reg8 |= SFR_RXCOE_IP | SFR_RXCOE_TCP | SFR_RXCOE_UDP |
				SFR_RXCOE_TCPV6 | SFR_RXCOE_UDPV6;
		}

		aqc111_write_cmd(dev, AQ_ACCESS_MAC, SFR_RXCOE_CTL,
				 1, 1, &reg8);
	}
	if (changed & NETIF_F_HW_VLAN_CTAG_FILTER) {
		if (features & NETIF_F_HW_VLAN_CTAG_FILTER) {
			u16 i = 0;

			for (i = 0; i < 256; i++) {
				/* Address */
				reg8 = i;
				aqc111_write_cmd(dev, AQ_ACCESS_MAC,
						 SFR_VLAN_ID_ADDRESS,
						 1, 1, &reg8);
				/* Data */
				aqc111_write16_cmd(dev, AQ_ACCESS_MAC,
						   SFR_VLAN_ID_DATA0,
						   2, &reg16);
				reg8 = SFR_VLAN_CONTROL_WE;
				aqc111_write_cmd(dev, AQ_ACCESS_MAC,
						 SFR_VLAN_ID_CONTROL,
						 1, 1, &reg8);
			}
			aqc111_read_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL,
					1, 1, &reg8);
			reg8 |= SFR_VLAN_CONTROL_VFE;
			aqc111_write_cmd(dev, AQ_ACCESS_MAC,
					 SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
		} else {
			aqc111_read_cmd(dev, AQ_ACCESS_MAC, SFR_VLAN_ID_CONTROL,
					1, 1, &reg8);
			reg8 &= ~SFR_VLAN_CONTROL_VFE;
			aqc111_write_cmd(dev, AQ_ACCESS_MAC,
					 SFR_VLAN_ID_CONTROL, 1, 1, &reg8);
		}
	}

	return 0;
}