#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {TYPE_3__* pdev; } ;
struct idt_ntb_dev {size_t port; size_t* port_idx_map; size_t* part_idx_map; size_t peer_cnt; TYPE_4__ ntb; TYPE_2__* peers; TYPE_1__* swcfg; void* part; } ;
struct TYPE_12__ {int /*<<< orphan*/  sts; } ;
struct TYPE_11__ {int /*<<< orphan*/  sts; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {unsigned char port; unsigned char part; } ;
struct TYPE_7__ {unsigned char port_cnt; unsigned char* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENODEV ; 
 void* GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDT_NT_PCIELCAP ; 
 scalar_t__ IS_FLD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT ; 
 int /*<<< orphan*/  NTDMA ; 
 int /*<<< orphan*/  PCIELCAP_PORTNUM ; 
 int /*<<< orphan*/  SWPARTxSTS_STATE ; 
 int /*<<< orphan*/  SWPORTxSTS_MODE ; 
 int /*<<< orphan*/  SWPORTxSTS_SWPART ; 
 int /*<<< orphan*/  USNT ; 
 int /*<<< orphan*/  USNTDMA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char,size_t) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  idt_nt_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_sw_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__* partdata_tbl ; 
 TYPE_5__* portdata_tbl ; 

__attribute__((used)) static int idt_scan_ports(struct idt_ntb_dev *ndev)
{
	unsigned char pidx, port, part;
	u32 data, portsts, partsts;

	/* Retrieve the local port number */
	data = idt_nt_read(ndev, IDT_NT_PCIELCAP);
	ndev->port = GET_FIELD(PCIELCAP_PORTNUM, data);

	/* Retrieve the local partition number */
	portsts = idt_sw_read(ndev, portdata_tbl[ndev->port].sts);
	ndev->part = GET_FIELD(SWPORTxSTS_SWPART, portsts);

	/* Initialize port/partition -> index tables with invalid values */
	memset(ndev->port_idx_map, -EINVAL, sizeof(ndev->port_idx_map));
	memset(ndev->part_idx_map, -EINVAL, sizeof(ndev->part_idx_map));

	/*
	 * Walk over all the possible ports checking whether any of them has
	 * NT-function activated
	 */
	ndev->peer_cnt = 0;
	for (pidx = 0; pidx < ndev->swcfg->port_cnt; pidx++) {
		port = ndev->swcfg->ports[pidx];
		/* Skip local port */
		if (port == ndev->port)
			continue;

		/* Read the port status register to get it partition */
		portsts = idt_sw_read(ndev, portdata_tbl[port].sts);
		part = GET_FIELD(SWPORTxSTS_SWPART, portsts);

		/* Retrieve the partition status */
		partsts = idt_sw_read(ndev, partdata_tbl[part].sts);
		/* Check if partition state is active and port has NTB */
		if (IS_FLD_SET(SWPARTxSTS_STATE, partsts, ACT) &&
		    (IS_FLD_SET(SWPORTxSTS_MODE, portsts, NT) ||
		     IS_FLD_SET(SWPORTxSTS_MODE, portsts, USNT) ||
		     IS_FLD_SET(SWPORTxSTS_MODE, portsts, USNTDMA) ||
		     IS_FLD_SET(SWPORTxSTS_MODE, portsts, NTDMA))) {
			/* Save the port and partition numbers */
			ndev->peers[ndev->peer_cnt].port = port;
			ndev->peers[ndev->peer_cnt].part = part;
			/* Fill in the port/partition -> index tables */
			ndev->port_idx_map[port] = ndev->peer_cnt;
			ndev->part_idx_map[part] = ndev->peer_cnt;
			ndev->peer_cnt++;
		}
	}

	dev_dbg(&ndev->ntb.pdev->dev, "Local port: %hhu, num of peers: %hhu\n",
		ndev->port, ndev->peer_cnt);

	/* It's useless to have this driver loaded if there is no any peer */
	if (ndev->peer_cnt == 0) {
		dev_warn(&ndev->ntb.pdev->dev, "No active peer found\n");
		return -ENODEV;
	}

	return 0;
}