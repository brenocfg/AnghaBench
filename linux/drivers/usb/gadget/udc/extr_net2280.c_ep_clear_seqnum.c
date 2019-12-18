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
struct net2280_ep {size_t num; struct net2280* dev; } ;
struct net2280 {TYPE_1__* plregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  pl_ep_ctrl; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQUENCE_NUMBER_RESET ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ep_clear_seqnum(struct net2280_ep *ep)
{
	struct net2280 *dev = ep->dev;
	u32 val;
	static const u32 ep_pl[9] = { 0, 3, 4, 7, 8, 2, 5, 6, 9 };

	val = readl(&dev->plregs->pl_ep_ctrl) & ~0x1f;
	val |= ep_pl[ep->num];
	writel(val, &dev->plregs->pl_ep_ctrl);
	val |= BIT(SEQUENCE_NUMBER_RESET);
	writel(val, &dev->plregs->pl_ep_ctrl);

	return;
}