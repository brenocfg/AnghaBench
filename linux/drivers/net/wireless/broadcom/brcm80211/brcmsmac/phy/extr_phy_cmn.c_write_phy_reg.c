#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct brcms_phy {scalar_t__ phy_wreg; scalar_t__ phy_wreg_limit; TYPE_2__* d11core; } ;
struct TYPE_7__ {TYPE_1__* bus; } ;
struct TYPE_6__ {scalar_t__ hosttype; } ;

/* Variables and functions */
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_read16 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_wflush16 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_write16 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_write32 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phyregaddr ; 
 int /*<<< orphan*/  phyregdata ; 
 int /*<<< orphan*/  phyversion ; 

void write_phy_reg(struct brcms_phy *pi, u16 addr, u16 val)
{
#ifdef CONFIG_BCM47XX
	bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr), addr);
	bcma_write16(pi->d11core, D11REGOFFS(phyregdata), val);
	if (addr == 0x72)
		(void)bcma_read16(pi->d11core, D11REGOFFS(phyregdata));
#else
	bcma_write32(pi->d11core, D11REGOFFS(phyregaddr), addr | (val << 16));
	if ((pi->d11core->bus->hosttype == BCMA_HOSTTYPE_PCI) &&
	    (++pi->phy_wreg >= pi->phy_wreg_limit)) {
		pi->phy_wreg = 0;
		(void)bcma_read16(pi->d11core, D11REGOFFS(phyversion));
	}
#endif
}