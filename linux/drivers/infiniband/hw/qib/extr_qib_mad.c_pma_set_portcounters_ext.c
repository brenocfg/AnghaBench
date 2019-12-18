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
typedef  void* u64 ;
struct qib_pportdata {int dummy; } ;
struct qib_pma_counters {int /*<<< orphan*/  n_multicast_rcv; int /*<<< orphan*/  n_multicast_xmit; int /*<<< orphan*/  n_unicast_rcv; int /*<<< orphan*/  n_unicast_xmit; } ;
struct qib_ibport {int /*<<< orphan*/  z_multicast_rcv; int /*<<< orphan*/  z_multicast_xmit; int /*<<< orphan*/  z_unicast_rcv; int /*<<< orphan*/  z_unicast_xmit; void* z_port_rcv_packets; void* z_port_xmit_packets; void* z_port_rcv_data; void* z_port_xmit_data; } ;
struct ib_pma_portcounters {int counter_select; } ;
struct ib_pma_mad {scalar_t__ data; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_PMA_SELX_PORT_MULTI_RCV_PACKETS ; 
 int IB_PMA_SELX_PORT_MULTI_XMIT_PACKETS ; 
 int IB_PMA_SELX_PORT_RCV_DATA ; 
 int IB_PMA_SELX_PORT_RCV_PACKETS ; 
 int IB_PMA_SELX_PORT_UNI_RCV_PACKETS ; 
 int IB_PMA_SELX_PORT_UNI_XMIT_PACKETS ; 
 int IB_PMA_SELX_PORT_XMIT_DATA ; 
 int IB_PMA_SELX_PORT_XMIT_PACKETS ; 
 int pma_get_portcounters_ext (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_snapshot_counters (struct qib_pportdata*,void**,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  qib_snapshot_pmacounters (struct qib_ibport*,struct qib_pma_counters*) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pma_set_portcounters_ext(struct ib_pma_mad *pmp,
				    struct ib_device *ibdev, u8 port)
{
	struct ib_pma_portcounters *p = (struct ib_pma_portcounters *)
		pmp->data;
	struct qib_ibport *ibp = to_iport(ibdev, port);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	u64 swords, rwords, spkts, rpkts, xwait;
	struct qib_pma_counters pma;

	qib_snapshot_counters(ppd, &swords, &rwords, &spkts, &rpkts, &xwait);

	if (p->counter_select & IB_PMA_SELX_PORT_XMIT_DATA)
		ibp->z_port_xmit_data = swords;

	if (p->counter_select & IB_PMA_SELX_PORT_RCV_DATA)
		ibp->z_port_rcv_data = rwords;

	if (p->counter_select & IB_PMA_SELX_PORT_XMIT_PACKETS)
		ibp->z_port_xmit_packets = spkts;

	if (p->counter_select & IB_PMA_SELX_PORT_RCV_PACKETS)
		ibp->z_port_rcv_packets = rpkts;

	qib_snapshot_pmacounters(ibp, &pma);

	if (p->counter_select & IB_PMA_SELX_PORT_UNI_XMIT_PACKETS)
		ibp->z_unicast_xmit = pma.n_unicast_xmit;

	if (p->counter_select & IB_PMA_SELX_PORT_UNI_RCV_PACKETS)
		ibp->z_unicast_rcv = pma.n_unicast_rcv;

	if (p->counter_select & IB_PMA_SELX_PORT_MULTI_XMIT_PACKETS)
		ibp->z_multicast_xmit = pma.n_multicast_xmit;

	if (p->counter_select & IB_PMA_SELX_PORT_MULTI_RCV_PACKETS)
		ibp->z_multicast_rcv = pma.n_multicast_rcv;

	return pma_get_portcounters_ext(pmp, ibdev, port);
}