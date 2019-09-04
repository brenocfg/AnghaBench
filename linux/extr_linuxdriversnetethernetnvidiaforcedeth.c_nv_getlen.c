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
struct vlan_ethhdr {scalar_t__ h_vlan_proto; int /*<<< orphan*/  h_vlan_encapsulated_proto; } ;
struct net_device {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int ETH_DATA_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int ETH_ZLEN ; 
 int VLAN_HLEN ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nv_getlen(struct net_device *dev, void *packet, int datalen)
{
	int hdrlen;	/* length of the 802 header */
	int protolen;	/* length as stored in the proto field */

	/* 1) calculate len according to header */
	if (((struct vlan_ethhdr *)packet)->h_vlan_proto == htons(ETH_P_8021Q)) {
		protolen = ntohs(((struct vlan_ethhdr *)packet)->h_vlan_encapsulated_proto);
		hdrlen = VLAN_HLEN;
	} else {
		protolen = ntohs(((struct ethhdr *)packet)->h_proto);
		hdrlen = ETH_HLEN;
	}
	if (protolen > ETH_DATA_LEN)
		return datalen; /* Value in proto field not a len, no checks possible */

	protolen += hdrlen;
	/* consistency checks: */
	if (datalen > ETH_ZLEN) {
		if (datalen >= protolen) {
			/* more data on wire than in 802 header, trim of
			 * additional data.
			 */
			return protolen;
		} else {
			/* less data on wire than mentioned in header.
			 * Discard the packet.
			 */
			return -1;
		}
	} else {
		/* short packet. Accept only if 802 values are also short */
		if (protolen > ETH_ZLEN) {
			return -1;
		}
		return datalen;
	}
}