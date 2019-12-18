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
struct rc_dev {int dummy; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* send_pulse ) (unsigned int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_space ) () ;} ;

/* Variables and functions */
 size_t IR_IRDEO ; 
 TYPE_1__* hardware ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  off () ; 
 int /*<<< orphan*/  on () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (unsigned int,int /*<<< orphan*/ ) ; 
 size_t type ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int serial_ir_tx(struct rc_dev *dev, unsigned int *txbuf,
			unsigned int count)
{
	unsigned long flags;
	ktime_t edge;
	s64 delta;
	int i;

	spin_lock_irqsave(&hardware[type].lock, flags);
	if (type == IR_IRDEO) {
		/* DTR, RTS down */
		on();
	}

	edge = ktime_get();
	for (i = 0; i < count; i++) {
		if (i % 2)
			hardware[type].send_space();
		else
			hardware[type].send_pulse(txbuf[i], edge);

		edge = ktime_add_us(edge, txbuf[i]);
		delta = ktime_us_delta(edge, ktime_get());
		if (delta > 25) {
			spin_unlock_irqrestore(&hardware[type].lock, flags);
			usleep_range(delta - 25, delta + 25);
			spin_lock_irqsave(&hardware[type].lock, flags);
		} else if (delta > 0) {
			udelay(delta);
		}
	}
	off();
	spin_unlock_irqrestore(&hardware[type].lock, flags);
	return count;
}