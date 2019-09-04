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
struct rc_dev {struct gpio_ir* priv; } ;
struct gpio_ir {int duty_cycle; int /*<<< orphan*/  lock; int /*<<< orphan*/  gpio; int /*<<< orphan*/  carrier; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int gpio_ir_tx(struct rc_dev *dev, unsigned int *txbuf,
		      unsigned int count)
{
	struct gpio_ir *gpio_ir = dev->priv;
	unsigned long flags;
	ktime_t edge;
	/*
	 * delta should never exceed 0.5 seconds (IR_MAX_DURATION) and on
	 * m68k ndelay(s64) does not compile; so use s32 rather than s64.
	 */
	s32 delta;
	int i;
	unsigned int pulse, space;

	/* Ensure the dividend fits into 32 bit */
	pulse = DIV_ROUND_CLOSEST(gpio_ir->duty_cycle * (NSEC_PER_SEC / 100),
				  gpio_ir->carrier);
	space = DIV_ROUND_CLOSEST((100 - gpio_ir->duty_cycle) *
				  (NSEC_PER_SEC / 100), gpio_ir->carrier);

	spin_lock_irqsave(&gpio_ir->lock, flags);

	edge = ktime_get();

	for (i = 0; i < count; i++) {
		if (i % 2) {
			// space
			edge = ktime_add_us(edge, txbuf[i]);
			delta = ktime_us_delta(edge, ktime_get());
			if (delta > 10) {
				spin_unlock_irqrestore(&gpio_ir->lock, flags);
				usleep_range(delta, delta + 10);
				spin_lock_irqsave(&gpio_ir->lock, flags);
			} else if (delta > 0) {
				udelay(delta);
			}
		} else {
			// pulse
			ktime_t last = ktime_add_us(edge, txbuf[i]);

			while (ktime_before(ktime_get(), last)) {
				gpiod_set_value(gpio_ir->gpio, 1);
				edge = ktime_add_ns(edge, pulse);
				delta = ktime_to_ns(ktime_sub(edge,
							      ktime_get()));
				if (delta > 0)
					ndelay(delta);
				gpiod_set_value(gpio_ir->gpio, 0);
				edge = ktime_add_ns(edge, space);
				delta = ktime_to_ns(ktime_sub(edge,
							      ktime_get()));
				if (delta > 0)
					ndelay(delta);
			}

			edge = last;
		}
	}

	spin_unlock_irqrestore(&gpio_ir->lock, flags);

	return count;
}