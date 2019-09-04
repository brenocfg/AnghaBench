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
typedef  scalar_t__ u32 ;
struct ar2315_pci_ctrl {scalar_t__ mmr_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void ar2315_pci_reg_write(struct ar2315_pci_ctrl *apc, u32 reg,
					u32 val)
{
	__raw_writel(val, apc->mmr_mem + reg);
}