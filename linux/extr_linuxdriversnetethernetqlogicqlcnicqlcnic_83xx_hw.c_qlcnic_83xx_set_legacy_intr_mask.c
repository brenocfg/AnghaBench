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
struct qlcnic_adapter {scalar_t__ tgt_mask_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void qlcnic_83xx_set_legacy_intr_mask(struct qlcnic_adapter *adapter)
{
	if (adapter->tgt_mask_reg)
		writel(1, adapter->tgt_mask_reg);
}