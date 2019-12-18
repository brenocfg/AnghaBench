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
struct dynpcc_info {scalar_t__ intr_cnt; int /*<<< orphan*/  last_pkts; int /*<<< orphan*/  last_bytes; } ;
struct jme_adapter {struct dynpcc_info dpi; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_TMCSR ; 
 TYPE_1__ NET_STAT (struct jme_adapter*) ; 
 int PCC_INTERVAL_US ; 
 int TMCSR_CNT ; 
 int TMCSR_EN ; 
 int /*<<< orphan*/  jwrite32 (struct jme_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
jme_start_pcc_timer(struct jme_adapter *jme)
{
	struct dynpcc_info *dpi = &(jme->dpi);
	dpi->last_bytes		= NET_STAT(jme).rx_bytes;
	dpi->last_pkts		= NET_STAT(jme).rx_packets;
	dpi->intr_cnt		= 0;
	jwrite32(jme, JME_TMCSR,
		TMCSR_EN | ((0xFFFFFF - PCC_INTERVAL_US) & TMCSR_CNT));
}