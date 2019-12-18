#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  tx_pause_frames; int /*<<< orphan*/  rx_pause_frames; } ;
struct TYPE_4__ {TYPE_1__ macb; } ;
struct macb {scalar_t__ (* macb_reg_readl ) (struct macb*,int) ;TYPE_2__ hw_stats; } ;

/* Variables and functions */
 int MACB_PFR ; 
 int MACB_TPF ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ stub1 (struct macb*,int) ; 

__attribute__((used)) static void macb_update_stats(struct macb *bp)
{
	u32 *p = &bp->hw_stats.macb.rx_pause_frames;
	u32 *end = &bp->hw_stats.macb.tx_pause_frames + 1;
	int offset = MACB_PFR;

	WARN_ON((unsigned long)(end - p - 1) != (MACB_TPF - MACB_PFR) / 4);

	for (; p < end; p++, offset += 4)
		*p += bp->macb_reg_readl(bp, offset);
}