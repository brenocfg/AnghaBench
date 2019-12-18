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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * regmap; } ;
struct ci_hdrc {TYPE_1__ hw_bank; } ;
typedef  enum ci_hw_regs { ____Placeholder_ci_hw_regs } ci_hw_regs ;

/* Variables and functions */
 int /*<<< orphan*/  __hw_write (struct ci_hdrc*,int,int /*<<< orphan*/ ) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 hw_test_and_clear(struct ci_hdrc *ci, enum ci_hw_regs reg,
				    u32 mask)
{
	u32 val = ioread32(ci->hw_bank.regmap[reg]) & mask;

	__hw_write(ci, val, ci->hw_bank.regmap[reg]);
	return val;
}