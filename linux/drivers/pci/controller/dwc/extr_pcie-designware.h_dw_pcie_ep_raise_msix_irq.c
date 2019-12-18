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
typedef  int /*<<< orphan*/  u16 ;
struct dw_pcie_ep {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int dw_pcie_ep_raise_msix_irq(struct dw_pcie_ep *ep, u8 func_no,
					   u16 interrupt_num)
{
	return 0;
}