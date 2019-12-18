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
struct nx_host_sds_ring {int /*<<< orphan*/  napi; struct netxen_adapter* adapter; } ;
struct netxen_adapter {int /*<<< orphan*/  tgt_status_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t netxen_msi_intr(int irq, void *data)
{
	struct nx_host_sds_ring *sds_ring = data;
	struct netxen_adapter *adapter = sds_ring->adapter;

	/* clear interrupt */
	writel(0xffffffff, adapter->tgt_status_reg);

	napi_schedule(&sds_ring->napi);
	return IRQ_HANDLED;
}