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
struct TYPE_2__ {int* msg; scalar_t__ len; } ;
struct stm32_cec {int irq_status; TYPE_1__ rx_msg; int /*<<< orphan*/  adap; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC_RXDR ; 
 int RXACKE ; 
 int RXBR ; 
 int RXEND ; 
 int RXOVR ; 
 int /*<<< orphan*/  cec_received_msg (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void stm32_rx_done(struct stm32_cec *cec, u32 status)
{
	if (cec->irq_status & (RXACKE | RXOVR)) {
		cec->rx_msg.len = 0;
		return;
	}

	if (cec->irq_status & RXBR) {
		u32 val;

		regmap_read(cec->regmap, CEC_RXDR, &val);
		cec->rx_msg.msg[cec->rx_msg.len++] = val & 0xFF;
	}

	if (cec->irq_status & RXEND) {
		cec_received_msg(cec->adap, &cec->rx_msg);
		cec->rx_msg.len = 0;
	}
}