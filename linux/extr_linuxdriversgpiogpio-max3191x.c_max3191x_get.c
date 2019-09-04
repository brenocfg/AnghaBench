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
typedef  unsigned int u8 ;
struct TYPE_2__ {scalar_t__ rx_buf; } ;
struct max3191x_chip {int /*<<< orphan*/  lock; TYPE_1__ xfer; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int MAX3191X_NGPIO ; 
 struct max3191x_chip* gpiochip_get_data (struct gpio_chip*) ; 
 scalar_t__ max3191x_chip_is_faulting (struct max3191x_chip*,int) ; 
 int max3191x_readout_locked (struct max3191x_chip*) ; 
 int max3191x_wordlen (struct max3191x_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max3191x_get(struct gpio_chip *gpio, unsigned int offset)
{
	struct max3191x_chip *max3191x = gpiochip_get_data(gpio);
	int ret, chipnum, wordlen = max3191x_wordlen(max3191x);
	u8 in;

	mutex_lock(&max3191x->lock);
	ret = max3191x_readout_locked(max3191x);
	if (ret)
		goto out_unlock;

	chipnum = offset / MAX3191X_NGPIO;
	if (max3191x_chip_is_faulting(max3191x, chipnum)) {
		ret = -EIO;
		goto out_unlock;
	}

	in = ((u8 *)max3191x->xfer.rx_buf)[chipnum * wordlen];
	ret = (in >> (offset % MAX3191X_NGPIO)) & 1;

out_unlock:
	mutex_unlock(&max3191x->lock);
	return ret;
}