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

/* Variables and functions */
 int /*<<< orphan*/  GBECONT ; 
 int GBECONT_RMII0 ; 
 int GBECONT_RMII1 ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh7757_eth_set_mdio_gate(void *addr)
{
	if (((unsigned long)addr & 0x00000fff) < 0x0800)
		writel(readl(GBECONT) | GBECONT_RMII0, GBECONT);
	else
		writel(readl(GBECONT) | GBECONT_RMII1, GBECONT);
}