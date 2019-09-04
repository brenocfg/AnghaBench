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
typedef  int /*<<< orphan*/  u8 ;
struct riic_dev {scalar_t__ bytes_left; scalar_t__ base; int /*<<< orphan*/ * buf; TYPE_1__* msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int flags; scalar_t__ len; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  ICIER_RIE ; 
 int /*<<< orphan*/  ICIER_TEIE ; 
 int /*<<< orphan*/  ICIER_TIE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ RIIC_ICDRT ; 
 int /*<<< orphan*/  RIIC_ICIER ; 
 scalar_t__ RIIC_INIT_MSG ; 
 int /*<<< orphan*/  i2c_8bit_addr_from_msg (TYPE_1__*) ; 
 int /*<<< orphan*/  riic_clear_set_bit (struct riic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t riic_tdre_isr(int irq, void *data)
{
	struct riic_dev *riic = data;
	u8 val;

	if (!riic->bytes_left)
		return IRQ_NONE;

	if (riic->bytes_left == RIIC_INIT_MSG) {
		if (riic->msg->flags & I2C_M_RD)
			/* On read, switch over to receive interrupt */
			riic_clear_set_bit(riic, ICIER_TIE, ICIER_RIE, RIIC_ICIER);
		else
			/* On write, initialize length */
			riic->bytes_left = riic->msg->len;

		val = i2c_8bit_addr_from_msg(riic->msg);
	} else {
		val = *riic->buf;
		riic->buf++;
		riic->bytes_left--;
	}

	/*
	 * Switch to transmission ended interrupt when done. Do check here
	 * after bytes_left was initialized to support SMBUS_QUICK (new msg has
	 * 0 length then)
	 */
	if (riic->bytes_left == 0)
		riic_clear_set_bit(riic, ICIER_TIE, ICIER_TEIE, RIIC_ICIER);

	/*
	 * This acks the TIE interrupt. We get another TIE immediately if our
	 * value could be moved to the shadow shift register right away. So
	 * this must be after updates to ICIER (where we want to disable TIE)!
	 */
	writeb(val, riic->base + RIIC_ICDRT);

	return IRQ_HANDLED;
}