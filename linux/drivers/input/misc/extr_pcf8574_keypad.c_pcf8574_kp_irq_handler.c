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
struct kp_data {unsigned char laststate; unsigned short* btncode; int /*<<< orphan*/  idev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned char ARRAY_SIZE (unsigned short*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,unsigned short,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 unsigned char read_state (struct kp_data*) ; 

__attribute__((used)) static irqreturn_t pcf8574_kp_irq_handler(int irq, void *dev_id)
{
	struct kp_data *lp = dev_id;
	unsigned char nextstate = read_state(lp);

	if (lp->laststate != nextstate) {
		int key_down = nextstate < ARRAY_SIZE(lp->btncode);
		unsigned short keycode = key_down ?
			lp->btncode[nextstate] : lp->btncode[lp->laststate];

		input_report_key(lp->idev, keycode, key_down);
		input_sync(lp->idev);

		lp->laststate = nextstate;
	}

	return IRQ_HANDLED;
}