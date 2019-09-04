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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ read_phy_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_phy_register(u64 regbase, u32 addr, u32 physel, u8 xdata)
{
	u8 data;

	data = read_phy_reg(regbase, addr, physel);
	pr_info("PHY read addr = 0x%x physel = %d data = 0x%x %s\n",
		addr, physel, data, data == xdata ? "TRUE" : "FALSE");
}