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
struct bgx {int dummy; } ;

/* Variables and functions */
 scalar_t__ BGX_CMRX_RX_STAT0 ; 
 int /*<<< orphan*/  bgx_reg_read (struct bgx*,int,scalar_t__) ; 
 struct bgx* get_bgx (int,int) ; 

u64 bgx_get_rx_stats(int node, int bgx_idx, int lmac, int idx)
{
	struct bgx *bgx;

	bgx = get_bgx(node, bgx_idx);
	if (!bgx)
		return 0;

	if (idx > 8)
		lmac = 0;
	return bgx_reg_read(bgx, lmac, BGX_CMRX_RX_STAT0 + (idx * 8));
}