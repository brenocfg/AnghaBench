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
typedef  scalar_t__ u32 ;
struct platform_mhu_link {scalar_t__ tx_reg; } ;
struct mbox_chan {struct platform_mhu_link* con_priv; } ;

/* Variables and functions */
 scalar_t__ INTR_STAT_OFS ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static bool platform_mhu_last_tx_done(struct mbox_chan *chan)
{
	struct platform_mhu_link *mlink = chan->con_priv;
	u32 val = readl_relaxed(mlink->tx_reg + INTR_STAT_OFS);

	return (val == 0);
}