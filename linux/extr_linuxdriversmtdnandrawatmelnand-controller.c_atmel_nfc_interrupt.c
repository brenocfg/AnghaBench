#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  smc; } ;
struct TYPE_4__ {int wait; } ;
struct atmel_hsmc_nand_controller {int /*<<< orphan*/  complete; TYPE_1__ base; TYPE_2__ op; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HSMC_NFC_IDR ; 
 int /*<<< orphan*/  ATMEL_HSMC_NFC_SR ; 
 int ATMEL_HSMC_NFC_SR_ERRORS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int atmel_nfc_op_done (TYPE_2__*,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t atmel_nfc_interrupt(int irq, void *data)
{
	struct atmel_hsmc_nand_controller *nc = data;
	u32 sr, rcvd;
	bool done;

	regmap_read(nc->base.smc, ATMEL_HSMC_NFC_SR, &sr);

	rcvd = sr & (nc->op.wait | ATMEL_HSMC_NFC_SR_ERRORS);
	done = atmel_nfc_op_done(&nc->op, sr);

	if (rcvd)
		regmap_write(nc->base.smc, ATMEL_HSMC_NFC_IDR, rcvd);

	if (done)
		complete(&nc->complete);

	return rcvd ? IRQ_HANDLED : IRQ_NONE;
}