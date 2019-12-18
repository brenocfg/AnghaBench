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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct cdns_pcie {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ CDNS_PCIE_RP_BASE ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void cdns_pcie_rp_writeb(struct cdns_pcie *pcie,
				       u32 reg, u8 value)
{
	writeb(value, pcie->reg_base + CDNS_PCIE_RP_BASE + reg);
}