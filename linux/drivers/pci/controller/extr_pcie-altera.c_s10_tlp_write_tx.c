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
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP_TX_REG0 ; 
 int /*<<< orphan*/  S10_RP_TX_CNTRL ; 
 int /*<<< orphan*/  cra_writel (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s10_tlp_write_tx(struct altera_pcie *pcie, u32 reg0, u32 ctrl)
{
	cra_writel(pcie, reg0, RP_TX_REG0);
	cra_writel(pcie, ctrl, S10_RP_TX_CNTRL);
}