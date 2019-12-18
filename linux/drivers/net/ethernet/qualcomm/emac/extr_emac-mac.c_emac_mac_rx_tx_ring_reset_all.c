#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int count; TYPE_5__* rfbuff; scalar_t__ consume_idx; scalar_t__ produce_idx; } ;
struct TYPE_11__ {scalar_t__ consume_idx; scalar_t__ produce_idx; } ;
struct TYPE_14__ {TYPE_6__ rfd; TYPE_4__ rrd; } ;
struct TYPE_9__ {unsigned int count; TYPE_1__* tpbuff; scalar_t__ consume_idx; scalar_t__ produce_idx; } ;
struct TYPE_10__ {TYPE_2__ tpd; } ;
struct emac_adapter {TYPE_7__ rx_q; TYPE_3__ tx_q; } ;
struct TYPE_12__ {scalar_t__ dma_addr; } ;
struct TYPE_8__ {scalar_t__ dma_addr; } ;

/* Variables and functions */

__attribute__((used)) static void emac_mac_rx_tx_ring_reset_all(struct emac_adapter *adpt)
{
	unsigned int i;

	adpt->tx_q.tpd.produce_idx = 0;
	adpt->tx_q.tpd.consume_idx = 0;
	for (i = 0; i < adpt->tx_q.tpd.count; i++)
		adpt->tx_q.tpd.tpbuff[i].dma_addr = 0;

	adpt->rx_q.rrd.produce_idx = 0;
	adpt->rx_q.rrd.consume_idx = 0;
	adpt->rx_q.rfd.produce_idx = 0;
	adpt->rx_q.rfd.consume_idx = 0;
	for (i = 0; i < adpt->rx_q.rfd.count; i++)
		adpt->rx_q.rfd.rfbuff[i].dma_addr = 0;
}