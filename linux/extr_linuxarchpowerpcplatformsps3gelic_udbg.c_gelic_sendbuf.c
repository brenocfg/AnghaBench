#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct udphdr {int dummy; } ;
struct iphdr {int dummy; } ;
struct TYPE_5__ {int dmac_cmd_status; scalar_t__ data_status; scalar_t__ result_size; scalar_t__ buf_size; } ;
struct TYPE_8__ {TYPE_1__ descr; } ;
struct TYPE_7__ {int tot_len; int check; } ;
struct TYPE_6__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GELIC_BUS_ID ; 
 int GELIC_DESCR_DMA_CARDOWNED ; 
 int GELIC_DESCR_DMA_CMD_NO_CHKSUM ; 
 int GELIC_DESCR_DMA_STAT_MASK ; 
 int GELIC_DESCR_TX_DMA_FRAME_TAIL ; 
 int /*<<< orphan*/  GELIC_DEVICE_ID ; 
 int /*<<< orphan*/  bus_addr ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_4__ dbg ; 
 TYPE_3__* h_ip ; 
 TYPE_2__* h_udp ; 
 scalar_t__ header_size ; 
 int /*<<< orphan*/  lv1_net_start_tx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void gelic_sendbuf(int msgsize)
{
	u16 *p;
	u32 sum;
	int i;

	dbg.descr.buf_size = header_size + msgsize;
	h_ip->tot_len = msgsize + sizeof(struct udphdr) +
			     sizeof(struct iphdr);
	h_udp->len = msgsize + sizeof(struct udphdr);

	h_ip->check = 0;
	sum = 0;
	p = (u16 *)h_ip;
	for (i = 0; i < 5; i++)
		sum += *p++;
	h_ip->check = ~(sum + (sum >> 16));

	dbg.descr.dmac_cmd_status = GELIC_DESCR_DMA_CMD_NO_CHKSUM |
				    GELIC_DESCR_TX_DMA_FRAME_TAIL;
	dbg.descr.result_size = 0;
	dbg.descr.data_status = 0;

	wmb();

	lv1_net_start_tx_dma(GELIC_BUS_ID, GELIC_DEVICE_ID, bus_addr, 0);

	while ((dbg.descr.dmac_cmd_status & GELIC_DESCR_DMA_STAT_MASK) ==
	       GELIC_DESCR_DMA_CARDOWNED)
		cpu_relax();
}