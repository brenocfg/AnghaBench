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
struct TYPE_2__ {int mode; int preamble; } ;
union cvmx_smix_clk {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct cavium_mdiobus {int mode; scalar_t__ register_base; } ;
typedef  enum cavium_mdiobus_mode { ____Placeholder_cavium_mdiobus_mode } cavium_mdiobus_mode ;

/* Variables and functions */
 int C45 ; 
 scalar_t__ SMI_CLK ; 
 int /*<<< orphan*/  oct_mdio_readq (scalar_t__) ; 
 int /*<<< orphan*/  oct_mdio_writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void cavium_mdiobus_set_mode(struct cavium_mdiobus *p,
				    enum cavium_mdiobus_mode m)
{
	union cvmx_smix_clk smi_clk;

	if (m == p->mode)
		return;

	smi_clk.u64 = oct_mdio_readq(p->register_base + SMI_CLK);
	smi_clk.s.mode = (m == C45) ? 1 : 0;
	smi_clk.s.preamble = 1;
	oct_mdio_writeq(smi_clk.u64, p->register_base + SMI_CLK);
	p->mode = m;
}