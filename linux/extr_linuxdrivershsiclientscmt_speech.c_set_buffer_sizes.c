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
struct cs_hsi_iface {int rx_bufs; int tx_bufs; int flags; int rx_ptr_boundary; TYPE_1__* mmap_cfg; } ;
struct TYPE_2__ {int rx_bufs; int tx_bufs; int rx_ptr_boundary; } ;

/* Variables and functions */
 int CS_FEAT_ROLLING_RX_COUNTER ; 
 int RX_PTR_BOUNDARY_SHIFT ; 

__attribute__((used)) static void set_buffer_sizes(struct cs_hsi_iface *hi, int rx_bufs, int tx_bufs)
{
	hi->rx_bufs = rx_bufs;
	hi->tx_bufs = tx_bufs;
	hi->mmap_cfg->rx_bufs = rx_bufs;
	hi->mmap_cfg->tx_bufs = tx_bufs;

	if (hi->flags & CS_FEAT_ROLLING_RX_COUNTER) {
		/*
		 * For more robust overrun detection, let the rx
		 * pointer run in range 0..'boundary-1'. Boundary
		 * is a multiple of rx_bufs, and limited in max size
		 * by RX_PTR_MAX_SHIFT to allow for fast ptr-diff
		 * calculation.
		 */
		hi->rx_ptr_boundary = (rx_bufs << RX_PTR_BOUNDARY_SHIFT);
		hi->mmap_cfg->rx_ptr_boundary = hi->rx_ptr_boundary;
	} else {
		hi->rx_ptr_boundary = hi->rx_bufs;
	}
}