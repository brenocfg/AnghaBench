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
typedef  scalar_t__ u64 ;
struct vnet_port {scalar_t__ rmtu; int tso; scalar_t__ tsolen; } ;
struct TYPE_2__ {int /*<<< orphan*/  stype; int /*<<< orphan*/  sid; } ;
struct vio_net_attr_info {int xfer_mode; scalar_t__ addr_type; scalar_t__ mtu; int cflags; scalar_t__ ipv4_lso_maxlen; TYPE_1__ tag; int /*<<< orphan*/  options; int /*<<< orphan*/  plnk_updt; int /*<<< orphan*/  ack_freq; scalar_t__ addr; } ;
struct vio_driver_state {int dummy; } ;

/* Variables and functions */
 int ECONNRESET ; 
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  HS ; 
 int VIO_DRING_MODE ; 
 int VIO_NEW_DRING_MODE ; 
 int /*<<< orphan*/  VIO_SUBTYPE_ACK ; 
 int /*<<< orphan*/  VIO_SUBTYPE_NACK ; 
 int /*<<< orphan*/  VIO_TX_DRING ; 
 scalar_t__ VLAN_HLEN ; 
 scalar_t__ VNET_ADDR_ETHERMAC ; 
 int VNET_LSO_IPV4_CAPAB ; 
 scalar_t__ VNET_MAXPACKET ; 
 scalar_t__ VNET_MAXTSO ; 
 scalar_t__ VNET_MINTSO ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct vnet_port* to_vnet_port (struct vio_driver_state*) ; 
 int vio_ldc_send (struct vio_driver_state*,struct vio_net_attr_info*,int) ; 
 int /*<<< orphan*/  vio_send_sid (struct vio_driver_state*) ; 
 scalar_t__ vio_version_after (struct vio_driver_state*,int,int) ; 
 scalar_t__ vio_version_after_eq (struct vio_driver_state*,int,int) ; 
 scalar_t__ vio_version_before (struct vio_driver_state*,int,int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int handle_attr_info(struct vio_driver_state *vio,
			    struct vio_net_attr_info *pkt)
{
	struct vnet_port *port = to_vnet_port(vio);
	u64	localmtu;
	u8	xfer_mode;

	viodbg(HS, "GOT NET ATTR xmode[0x%x] atype[0x%x] addr[%llx] "
	       "ackfreq[%u] plnk_updt[0x%02x] opts[0x%02x] mtu[%llu] "
	       " (rmtu[%llu]) cflags[0x%04x] lso_max[%u]\n",
	       pkt->xfer_mode, pkt->addr_type,
	       (unsigned long long)pkt->addr,
	       pkt->ack_freq, pkt->plnk_updt, pkt->options,
	       (unsigned long long)pkt->mtu, port->rmtu, pkt->cflags,
	       pkt->ipv4_lso_maxlen);

	pkt->tag.sid = vio_send_sid(vio);

	xfer_mode = pkt->xfer_mode;
	/* for version < 1.2, VIO_DRING_MODE = 0x3 and no bitmask */
	if (vio_version_before(vio, 1, 2) && xfer_mode == VIO_DRING_MODE)
		xfer_mode = VIO_NEW_DRING_MODE;

	/* MTU negotiation:
	 *	< v1.3 - ETH_FRAME_LEN exactly
	 *	> v1.3 - MIN(pkt.mtu, VNET_MAXPACKET, port->rmtu) and change
	 *			pkt->mtu for ACK
	 *	= v1.3 - ETH_FRAME_LEN + VLAN_HLEN exactly
	 */
	if (vio_version_before(vio, 1, 3)) {
		localmtu = ETH_FRAME_LEN;
	} else if (vio_version_after(vio, 1, 3)) {
		localmtu = port->rmtu ? port->rmtu : VNET_MAXPACKET;
		localmtu = min(pkt->mtu, localmtu);
		pkt->mtu = localmtu;
	} else { /* v1.3 */
		localmtu = ETH_FRAME_LEN + VLAN_HLEN;
	}
	port->rmtu = localmtu;

	/* LSO negotiation */
	if (vio_version_after_eq(vio, 1, 7))
		port->tso &= !!(pkt->cflags & VNET_LSO_IPV4_CAPAB);
	else
		port->tso = false;
	if (port->tso) {
		if (!port->tsolen)
			port->tsolen = VNET_MAXTSO;
		port->tsolen = min(port->tsolen, pkt->ipv4_lso_maxlen);
		if (port->tsolen < VNET_MINTSO) {
			port->tso = false;
			port->tsolen = 0;
			pkt->cflags &= ~VNET_LSO_IPV4_CAPAB;
		}
		pkt->ipv4_lso_maxlen = port->tsolen;
	} else {
		pkt->cflags &= ~VNET_LSO_IPV4_CAPAB;
		pkt->ipv4_lso_maxlen = 0;
		port->tsolen = 0;
	}

	/* for version >= 1.6, ACK packet mode we support */
	if (vio_version_after_eq(vio, 1, 6)) {
		pkt->xfer_mode = VIO_NEW_DRING_MODE;
		pkt->options = VIO_TX_DRING;
	}

	if (!(xfer_mode | VIO_NEW_DRING_MODE) ||
	    pkt->addr_type != VNET_ADDR_ETHERMAC ||
	    pkt->mtu != localmtu) {
		viodbg(HS, "SEND NET ATTR NACK\n");

		pkt->tag.stype = VIO_SUBTYPE_NACK;

		(void)vio_ldc_send(vio, pkt, sizeof(*pkt));

		return -ECONNRESET;
	}

	viodbg(HS, "SEND NET ATTR ACK xmode[0x%x] atype[0x%x] "
	       "addr[%llx] ackfreq[%u] plnk_updt[0x%02x] opts[0x%02x] "
	       "mtu[%llu] (rmtu[%llu]) cflags[0x%04x] lso_max[%u]\n",
	       pkt->xfer_mode, pkt->addr_type,
	       (unsigned long long)pkt->addr,
	       pkt->ack_freq, pkt->plnk_updt, pkt->options,
	       (unsigned long long)pkt->mtu, port->rmtu, pkt->cflags,
	       pkt->ipv4_lso_maxlen);

	pkt->tag.stype = VIO_SUBTYPE_ACK;

	return vio_ldc_send(vio, pkt, sizeof(*pkt));
}