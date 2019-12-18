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
struct riic_dev {int /*<<< orphan*/  msg_done; scalar_t__ base; int /*<<< orphan*/  err; scalar_t__ is_last; scalar_t__ bytes_left; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  ICCR2_SP ; 
 int /*<<< orphan*/  ICIER_SPIE ; 
 int ICIER_TEIE ; 
 int ICSR2_NACKF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ RIIC_ICCR2 ; 
 scalar_t__ RIIC_ICDRR ; 
 scalar_t__ RIIC_ICIER ; 
 scalar_t__ RIIC_ICSR2 ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  riic_clear_set_bit (struct riic_dev*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t riic_tend_isr(int irq, void *data)
{
	struct riic_dev *riic = data;

	if (readb(riic->base + RIIC_ICSR2) & ICSR2_NACKF) {
		/* We got a NACKIE */
		readb(riic->base + RIIC_ICDRR);	/* dummy read */
		riic_clear_set_bit(riic, ICSR2_NACKF, 0, RIIC_ICSR2);
		riic->err = -ENXIO;
	} else if (riic->bytes_left) {
		return IRQ_NONE;
	}

	if (riic->is_last || riic->err) {
		riic_clear_set_bit(riic, ICIER_TEIE, ICIER_SPIE, RIIC_ICIER);
		writeb(ICCR2_SP, riic->base + RIIC_ICCR2);
	} else {
		/* Transfer is complete, but do not send STOP */
		riic_clear_set_bit(riic, ICIER_TEIE, 0, RIIC_ICIER);
		complete(&riic->msg_done);
	}

	return IRQ_HANDLED;
}