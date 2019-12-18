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
struct amd_mp2_dev {scalar_t__ mmio; } ;

/* Variables and functions */
 int AMD_C2P_MSG0 ; 
 int AMD_C2P_MSG9 ; 
 int AMD_P2C_MSG1 ; 
 int AMD_P2C_MSG2 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void amd_mp2_clear_reg(struct amd_mp2_dev *privdata)
{
	int reg;

	for (reg = AMD_C2P_MSG0; reg <= AMD_C2P_MSG9; reg += 4)
		writel(0, privdata->mmio + reg);

	for (reg = AMD_P2C_MSG1; reg <= AMD_P2C_MSG2; reg += 4)
		writel(0, privdata->mmio + reg);
}