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
typedef  int u64 ;
struct vnet_port {int rmtu; scalar_t__ tsolen; scalar_t__ tso; } ;
struct TYPE_2__ {int /*<<< orphan*/  sid; int /*<<< orphan*/  stype_env; int /*<<< orphan*/  stype; int /*<<< orphan*/  type; } ;
struct vio_net_attr_info {int addr; int mtu; scalar_t__ ipv4_lso_maxlen; int /*<<< orphan*/  cflags; int /*<<< orphan*/  options; int /*<<< orphan*/  plnk_updt; scalar_t__ ack_freq; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  xfer_mode; TYPE_1__ tag; } ;
struct vio_driver_state {int dummy; } ;
struct net_device {scalar_t__* dev_addr; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
 int ETH_FRAME_LEN ; 
 int /*<<< orphan*/  HS ; 
 int /*<<< orphan*/  PHYSLINK_UPDATE_NONE ; 
 int /*<<< orphan*/  VIO_ATTR_INFO ; 
 int /*<<< orphan*/  VIO_DRING_MODE ; 
 int /*<<< orphan*/  VIO_NEW_DRING_MODE ; 
 int /*<<< orphan*/  VIO_SUBTYPE_INFO ; 
 int /*<<< orphan*/  VIO_TX_DRING ; 
 int /*<<< orphan*/  VIO_TYPE_CTRL ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  VNET_ADDR_ETHERMAC ; 
 int /*<<< orphan*/  VNET_LSO_IPV4_CAPAB ; 
 int VNET_MAXPACKET ; 
 scalar_t__ VNET_MAXTSO ; 
 struct net_device* VNET_PORT_TO_NET_DEVICE (struct vnet_port*) ; 
 int /*<<< orphan*/  memset (struct vio_net_attr_info*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 struct vnet_port* to_vnet_port (struct vio_driver_state*) ; 
 int vio_ldc_send (struct vio_driver_state*,struct vio_net_attr_info*,int) ; 
 int /*<<< orphan*/  vio_send_sid (struct vio_driver_state*) ; 
 scalar_t__ vio_version_after (struct vio_driver_state*,int,int) ; 
 scalar_t__ vio_version_after_eq (struct vio_driver_state*,int,int) ; 
 scalar_t__ vio_version_before (struct vio_driver_state*,int,int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,scalar_t__) ; 
 int vnet_port_alloc_tx_ring (struct vnet_port*) ; 

int sunvnet_send_attr_common(struct vio_driver_state *vio)
{
	struct vnet_port *port = to_vnet_port(vio);
	struct net_device *dev = VNET_PORT_TO_NET_DEVICE(port);
	struct vio_net_attr_info pkt;
	int framelen = ETH_FRAME_LEN;
	int i, err;

	err = vnet_port_alloc_tx_ring(to_vnet_port(vio));
	if (err)
		return err;

	memset(&pkt, 0, sizeof(pkt));
	pkt.tag.type = VIO_TYPE_CTRL;
	pkt.tag.stype = VIO_SUBTYPE_INFO;
	pkt.tag.stype_env = VIO_ATTR_INFO;
	pkt.tag.sid = vio_send_sid(vio);
	if (vio_version_before(vio, 1, 2))
		pkt.xfer_mode = VIO_DRING_MODE;
	else
		pkt.xfer_mode = VIO_NEW_DRING_MODE;
	pkt.addr_type = VNET_ADDR_ETHERMAC;
	pkt.ack_freq = 0;
	for (i = 0; i < 6; i++)
		pkt.addr |= (u64)dev->dev_addr[i] << ((5 - i) * 8);
	if (vio_version_after(vio, 1, 3)) {
		if (port->rmtu) {
			port->rmtu = min(VNET_MAXPACKET, port->rmtu);
			pkt.mtu = port->rmtu;
		} else {
			port->rmtu = VNET_MAXPACKET;
			pkt.mtu = port->rmtu;
		}
		if (vio_version_after_eq(vio, 1, 6))
			pkt.options = VIO_TX_DRING;
	} else if (vio_version_before(vio, 1, 3)) {
		pkt.mtu = framelen;
	} else { /* v1.3 */
		pkt.mtu = framelen + VLAN_HLEN;
	}

	pkt.cflags = 0;
	if (vio_version_after_eq(vio, 1, 7) && port->tso) {
		pkt.cflags |= VNET_LSO_IPV4_CAPAB;
		if (!port->tsolen)
			port->tsolen = VNET_MAXTSO;
		pkt.ipv4_lso_maxlen = port->tsolen;
	}

	pkt.plnk_updt = PHYSLINK_UPDATE_NONE;

	viodbg(HS, "SEND NET ATTR xmode[0x%x] atype[0x%x] addr[%llx] "
	       "ackfreq[%u] plnk_updt[0x%02x] opts[0x%02x] mtu[%llu] "
	       "cflags[0x%04x] lso_max[%u]\n",
	       pkt.xfer_mode, pkt.addr_type,
	       (unsigned long long)pkt.addr,
	       pkt.ack_freq, pkt.plnk_updt, pkt.options,
	       (unsigned long long)pkt.mtu, pkt.cflags, pkt.ipv4_lso_maxlen);

	return vio_ldc_send(vio, &pkt, sizeof(pkt));
}