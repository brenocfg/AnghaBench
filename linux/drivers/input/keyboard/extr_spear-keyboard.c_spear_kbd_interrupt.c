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
typedef  size_t u32 ;
struct spear_kbd {unsigned int last_key; unsigned int* keycodes; scalar_t__ io_base; struct input_dev* input; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t DATA_COLUMN_MASK ; 
 scalar_t__ DATA_REG ; 
 size_t DATA_ROW_MASK ; 
 int /*<<< orphan*/  EV_MSC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int KEY_RESERVED ; 
 int /*<<< orphan*/  MSC_SCAN ; 
 size_t STATUS_DATA_AVAIL ; 
 scalar_t__ STATUS_REG ; 
 int /*<<< orphan*/  input_event (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 size_t readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t spear_kbd_interrupt(int irq, void *dev_id)
{
	struct spear_kbd *kbd = dev_id;
	struct input_dev *input = kbd->input;
	unsigned int key;
	u32 sts, val;

	sts = readl_relaxed(kbd->io_base + STATUS_REG);
	if (!(sts & STATUS_DATA_AVAIL))
		return IRQ_NONE;

	if (kbd->last_key != KEY_RESERVED) {
		input_report_key(input, kbd->last_key, 0);
		kbd->last_key = KEY_RESERVED;
	}

	/* following reads active (row, col) pair */
	val = readl_relaxed(kbd->io_base + DATA_REG) &
		(DATA_ROW_MASK | DATA_COLUMN_MASK);
	key = kbd->keycodes[val];

	input_event(input, EV_MSC, MSC_SCAN, val);
	input_report_key(input, key, 1);
	input_sync(input);

	kbd->last_key = key;

	/* clear interrupt */
	writel_relaxed(0, kbd->io_base + STATUS_REG);

	return IRQ_HANDLED;
}