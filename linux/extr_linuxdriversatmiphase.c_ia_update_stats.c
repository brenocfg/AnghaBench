#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rx_cell_cnt; int drop_rxpkt; int drop_rxcell; int tx_cell_cnt; scalar_t__ seg_reg; scalar_t__ reass_reg; int /*<<< orphan*/  carrier_detect; } ;
typedef  TYPE_1__ IADEV ;

/* Variables and functions */
 scalar_t__ CELL_CTR0 ; 
 scalar_t__ CELL_CTR1 ; 
 scalar_t__ CELL_CTR_HIGH_AUTO ; 
 scalar_t__ CELL_CTR_LO_AUTO ; 
 scalar_t__ DRP_PKT_CNTR ; 
 scalar_t__ ERR_CNTR ; 
 int readw (scalar_t__) ; 

__attribute__((used)) static void ia_update_stats(IADEV *iadev) {
    if (!iadev->carrier_detect)
        return;
    iadev->rx_cell_cnt += readw(iadev->reass_reg+CELL_CTR0)&0xffff;
    iadev->rx_cell_cnt += (readw(iadev->reass_reg+CELL_CTR1) & 0xffff) << 16;
    iadev->drop_rxpkt +=  readw(iadev->reass_reg + DRP_PKT_CNTR ) & 0xffff;
    iadev->drop_rxcell += readw(iadev->reass_reg + ERR_CNTR) & 0xffff;
    iadev->tx_cell_cnt += readw(iadev->seg_reg + CELL_CTR_LO_AUTO)&0xffff;
    iadev->tx_cell_cnt += (readw(iadev->seg_reg+CELL_CTR_HIGH_AUTO)&0xffff)<<16;
    return;
}