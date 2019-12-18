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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct spmi_pmic_arb {scalar_t__ rd_base; } ;

/* Variables and functions */
 scalar_t__ __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 

__attribute__((used)) static void
pmic_arb_read_data(struct spmi_pmic_arb *pmic_arb, u8 *buf, u32 reg, u8 bc)
{
	u32 data = __raw_readl(pmic_arb->rd_base + reg);

	memcpy(buf, &data, (bc & 3) + 1);
}