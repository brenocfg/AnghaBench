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
struct adf_etr_bank_data {int /*<<< orphan*/  resp_handler; int /*<<< orphan*/  bank_number; int /*<<< orphan*/  csr_addr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  WRITE_CSR_INT_FLAG_AND_COL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t adf_msix_isr_bundle(int irq, void *bank_ptr)
{
	struct adf_etr_bank_data *bank = bank_ptr;

	WRITE_CSR_INT_FLAG_AND_COL(bank->csr_addr, bank->bank_number, 0);
	tasklet_hi_schedule(&bank->resp_handler);
	return IRQ_HANDLED;
}