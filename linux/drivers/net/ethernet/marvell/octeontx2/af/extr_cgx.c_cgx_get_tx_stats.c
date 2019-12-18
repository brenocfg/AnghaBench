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
typedef  int /*<<< orphan*/  u64 ;
struct cgx {int lmac_count; } ;

/* Variables and functions */
 scalar_t__ CGXX_CMRX_TX_STAT0 ; 
 int ENODEV ; 
 int /*<<< orphan*/  cgx_read (struct cgx*,int,scalar_t__) ; 

int cgx_get_tx_stats(void *cgxd, int lmac_id, int idx, u64 *tx_stat)
{
	struct cgx *cgx = cgxd;

	if (!cgx || lmac_id >= cgx->lmac_count)
		return -ENODEV;
	*tx_stat = cgx_read(cgx, lmac_id, CGXX_CMRX_TX_STAT0 + (idx * 8));
	return 0;
}