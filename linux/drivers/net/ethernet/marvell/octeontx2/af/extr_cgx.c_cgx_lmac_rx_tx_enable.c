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
typedef  int u64 ;
struct cgx {int lmac_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGXX_CMRX_CFG ; 
 int CMR_EN ; 
 int DATA_PKT_RX_EN ; 
 int DATA_PKT_TX_EN ; 
 int ENODEV ; 
 int cgx_read (struct cgx*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgx_write (struct cgx*,int,int /*<<< orphan*/ ,int) ; 

int cgx_lmac_rx_tx_enable(void *cgxd, int lmac_id, bool enable)
{
	struct cgx *cgx = cgxd;
	u64 cfg;

	if (!cgx || lmac_id >= cgx->lmac_count)
		return -ENODEV;

	cfg = cgx_read(cgx, lmac_id, CGXX_CMRX_CFG);
	if (enable)
		cfg |= CMR_EN | DATA_PKT_RX_EN | DATA_PKT_TX_EN;
	else
		cfg &= ~(CMR_EN | DATA_PKT_RX_EN | DATA_PKT_TX_EN);
	cgx_write(cgx, lmac_id, CGXX_CMRX_CFG, cfg);
	return 0;
}