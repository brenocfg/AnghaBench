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
struct denali_nand_info {int max_banks; int active_bank; int /*<<< orphan*/  dev; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ DEVICE_RESET ; 
 int /*<<< orphan*/  DEVICE_RESET__BANK (int) ; 
 int INTR__INT_ACT ; 
 int INTR__RST_COMP ; 
 int INTR__TIME_OUT ; 
 int /*<<< orphan*/  denali_reset_irq (struct denali_nand_info*) ; 
 int denali_wait_for_irq (struct denali_nand_info*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void denali_reset_banks(struct denali_nand_info *denali)
{
	u32 irq_status;
	int i;

	for (i = 0; i < denali->max_banks; i++) {
		denali->active_bank = i;

		denali_reset_irq(denali);

		iowrite32(DEVICE_RESET__BANK(i),
			  denali->reg + DEVICE_RESET);

		irq_status = denali_wait_for_irq(denali,
			INTR__RST_COMP | INTR__INT_ACT | INTR__TIME_OUT);
		if (!(irq_status & INTR__INT_ACT))
			break;
	}

	dev_dbg(denali->dev, "%d chips connected\n", i);
	denali->max_banks = i;
}