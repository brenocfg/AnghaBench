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
typedef  int u32 ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PBC_INTMASK_SET_REG ; 
 int /*<<< orphan*/  PBC_INTSTATUS_REG ; 
 int /*<<< orphan*/  domain ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int imx_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mx31ads_expio_irq_handler(struct irq_desc *desc)
{
	u32 imr_val;
	u32 int_valid;
	u32 expio_irq;

	imr_val = imx_readw(PBC_INTMASK_SET_REG);
	int_valid = imx_readw(PBC_INTSTATUS_REG) & imr_val;

	expio_irq = 0;
	for (; int_valid != 0; int_valid >>= 1, expio_irq++) {
		if ((int_valid & 1) == 0)
			continue;

		generic_handle_irq(irq_find_mapping(domain, expio_irq));
	}
}