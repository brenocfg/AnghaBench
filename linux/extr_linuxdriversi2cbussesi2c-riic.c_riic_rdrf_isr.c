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
struct riic_dev {int bytes_left; int /*<<< orphan*/ * buf; scalar_t__ base; scalar_t__ is_last; TYPE_1__* msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICCR2_SP ; 
 int /*<<< orphan*/  ICIER_SPIE ; 
 int /*<<< orphan*/  ICMR3_ACKBT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ RIIC_ICCR2 ; 
 scalar_t__ RIIC_ICDRR ; 
 int /*<<< orphan*/  RIIC_ICIER ; 
 int /*<<< orphan*/  RIIC_ICMR3 ; 
 int RIIC_INIT_MSG ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  riic_clear_set_bit (struct riic_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t riic_rdrf_isr(int irq, void *data)
{
	struct riic_dev *riic = data;

	if (!riic->bytes_left)
		return IRQ_NONE;

	if (riic->bytes_left == RIIC_INIT_MSG) {
		riic->bytes_left = riic->msg->len;
		readb(riic->base + RIIC_ICDRR);	/* dummy read */
		return IRQ_HANDLED;
	}

	if (riic->bytes_left == 1) {
		/* STOP must come before we set ACKBT! */
		if (riic->is_last) {
			riic_clear_set_bit(riic, 0, ICIER_SPIE, RIIC_ICIER);
			writeb(ICCR2_SP, riic->base + RIIC_ICCR2);
		}

		riic_clear_set_bit(riic, 0, ICMR3_ACKBT, RIIC_ICMR3);

	} else {
		riic_clear_set_bit(riic, ICMR3_ACKBT, 0, RIIC_ICMR3);
	}

	/* Reading acks the RIE interrupt */
	*riic->buf = readb(riic->base + RIIC_ICDRR);
	riic->buf++;
	riic->bytes_left--;

	return IRQ_HANDLED;
}