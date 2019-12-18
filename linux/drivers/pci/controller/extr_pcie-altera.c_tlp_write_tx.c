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
struct tlp_rp_regpair_t {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  reg1; int /*<<< orphan*/  reg0; } ;
struct altera_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RP_TX_CNTRL ; 
 int /*<<< orphan*/  RP_TX_REG0 ; 
 int /*<<< orphan*/  RP_TX_REG1 ; 
 int /*<<< orphan*/  cra_writel (struct altera_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tlp_write_tx(struct altera_pcie *pcie,
			 struct tlp_rp_regpair_t *tlp_rp_regdata)
{
	cra_writel(pcie, tlp_rp_regdata->reg0, RP_TX_REG0);
	cra_writel(pcie, tlp_rp_regdata->reg1, RP_TX_REG1);
	cra_writel(pcie, tlp_rp_regdata->ctrl, RP_TX_CNTRL);
}