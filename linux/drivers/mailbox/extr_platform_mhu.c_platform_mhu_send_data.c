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
typedef  int /*<<< orphan*/  u32 ;
struct platform_mhu_link {scalar_t__ tx_reg; } ;
struct mbox_chan {struct platform_mhu_link* con_priv; } ;

/* Variables and functions */
 scalar_t__ INTR_SET_OFS ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int platform_mhu_send_data(struct mbox_chan *chan, void *data)
{
	struct platform_mhu_link *mlink = chan->con_priv;
	u32 *arg = data;

	writel_relaxed(*arg, mlink->tx_reg + INTR_SET_OFS);

	return 0;
}