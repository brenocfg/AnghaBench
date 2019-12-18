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
struct mt7621_pcie {int /*<<< orphan*/  perst; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERST_DELAY_US ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mt7621_perst_gpio_pcie_deassert(struct mt7621_pcie *pcie)
{
	gpiod_set_value(pcie->perst, 1);
	mdelay(PERST_DELAY_US);
}