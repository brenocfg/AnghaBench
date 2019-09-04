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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR2315_AHB_ERR0 ; 
 int /*<<< orphan*/  AR2315_AHB_ERR1 ; 
 int /*<<< orphan*/  AR2315_AHB_ERROR_DET ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ar2315_rst_reg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar2315_rst_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_restart (char*) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

__attribute__((used)) static irqreturn_t ar2315_ahb_err_handler(int cpl, void *dev_id)
{
	ar2315_rst_reg_write(AR2315_AHB_ERR0, AR2315_AHB_ERROR_DET);
	ar2315_rst_reg_read(AR2315_AHB_ERR1);

	pr_emerg("AHB fatal error\n");
	machine_restart("AHB error"); /* Catastrophic failure */

	return IRQ_HANDLED;
}