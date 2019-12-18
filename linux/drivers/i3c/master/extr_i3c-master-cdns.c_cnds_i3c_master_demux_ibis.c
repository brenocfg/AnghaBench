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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  wq; } ;
struct cdns_i3c_master {int /*<<< orphan*/  hj_work; TYPE_1__ base; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ IBIR ; 
 int IBIR_ERROR ; 
 int IBIR_TYPE (int) ; 
#define  IBIR_TYPE_HJ 130 
#define  IBIR_TYPE_IBI 129 
#define  IBIR_TYPE_MR 128 
 int /*<<< orphan*/  IBIR_XFER_BYTES (int) ; 
 scalar_t__ MST_ICR ; 
 int /*<<< orphan*/  MST_INT_IBIR_THR ; 
 scalar_t__ MST_STATUS0 ; 
 int MST_STATUS0_IBIR_EMP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cdns_i3c_master_handle_ibi (struct cdns_i3c_master*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cnds_i3c_master_demux_ibis(struct cdns_i3c_master *master)
{
	u32 status0;

	writel(MST_INT_IBIR_THR, master->regs + MST_ICR);

	for (status0 = readl(master->regs + MST_STATUS0);
	     !(status0 & MST_STATUS0_IBIR_EMP);
	     status0 = readl(master->regs + MST_STATUS0)) {
		u32 ibir = readl(master->regs + IBIR);

		switch (IBIR_TYPE(ibir)) {
		case IBIR_TYPE_IBI:
			cdns_i3c_master_handle_ibi(master, ibir);
			break;

		case IBIR_TYPE_HJ:
			WARN_ON(IBIR_XFER_BYTES(ibir) || (ibir & IBIR_ERROR));
			queue_work(master->base.wq, &master->hj_work);
			break;

		case IBIR_TYPE_MR:
			WARN_ON(IBIR_XFER_BYTES(ibir) || (ibir & IBIR_ERROR));
		default:
			break;
		}
	}
}