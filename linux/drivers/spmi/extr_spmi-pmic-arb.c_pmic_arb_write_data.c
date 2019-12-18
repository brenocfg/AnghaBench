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
struct spmi_pmic_arb {scalar_t__ wr_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int const*,int) ; 

__attribute__((used)) static void pmic_arb_write_data(struct spmi_pmic_arb *pmic_arb, const u8 *buf,
				u32 reg, u8 bc)
{
	u32 data = 0;

	memcpy(&data, buf, (bc & 3) + 1);
	__raw_writel(data, pmic_arb->wr_base + reg);
}