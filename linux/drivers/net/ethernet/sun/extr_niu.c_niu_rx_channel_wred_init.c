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
struct rx_ring_info {int /*<<< orphan*/  rx_channel; scalar_t__ syn_threshold; scalar_t__ syn_window; scalar_t__ nonsyn_threshold; scalar_t__ nonsyn_window; } ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDC_RED_PARA (int /*<<< orphan*/ ) ; 
 int RDC_RED_PARA_THRE_SHIFT ; 
 int RDC_RED_PARA_THRE_SYN_SHIFT ; 
 int RDC_RED_PARA_WIN_SHIFT ; 
 int RDC_RED_PARA_WIN_SYN_SHIFT ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_rx_channel_wred_init(struct niu *np, struct rx_ring_info *rp)
{
	u64 val;

	val = (((u64)rp->nonsyn_window << RDC_RED_PARA_WIN_SHIFT) |
	       ((u64)rp->nonsyn_threshold << RDC_RED_PARA_THRE_SHIFT) |
	       ((u64)rp->syn_window << RDC_RED_PARA_WIN_SYN_SHIFT) |
	       ((u64)rp->syn_threshold << RDC_RED_PARA_THRE_SYN_SHIFT));
	nw64(RDC_RED_PARA(rp->rx_channel), val);
}