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
struct meson_ir {int /*<<< orphan*/  lock; int /*<<< orphan*/  rc; scalar_t__ reg; } ;
struct ir_raw_event {int pulse; int /*<<< orphan*/  duration; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ IR_DEC_REG1 ; 
 scalar_t__ IR_DEC_STATUS ; 
 int MESON_TRATE ; 
 int /*<<< orphan*/  REG1_TIME_IV_MASK ; 
 int STATUS_IR_DEC_IN ; 
 int /*<<< orphan*/  US_TO_NS (int) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_timeout (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t meson_ir_irq(int irqno, void *dev_id)
{
	struct meson_ir *ir = dev_id;
	u32 duration, status;
	struct ir_raw_event rawir = {};

	spin_lock(&ir->lock);

	duration = readl_relaxed(ir->reg + IR_DEC_REG1);
	duration = FIELD_GET(REG1_TIME_IV_MASK, duration);
	rawir.duration = US_TO_NS(duration * MESON_TRATE);

	status = readl_relaxed(ir->reg + IR_DEC_STATUS);
	rawir.pulse = !!(status & STATUS_IR_DEC_IN);

	ir_raw_event_store_with_timeout(ir->rc, &rawir);

	spin_unlock(&ir->lock);

	return IRQ_HANDLED;
}