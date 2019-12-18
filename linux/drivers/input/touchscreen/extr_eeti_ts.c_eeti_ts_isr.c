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
struct eeti_ts {int /*<<< orphan*/  mutex; scalar_t__ attn_gpio; scalar_t__ running; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int eeti_ts_read (struct eeti_ts*) ; 
 int /*<<< orphan*/  gpiod_get_value_cansleep (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t eeti_ts_isr(int irq, void *dev_id)
{
	struct eeti_ts *eeti = dev_id;
	int error;

	mutex_lock(&eeti->mutex);

	do {
		/*
		 * If we have attention GPIO, trust it. Otherwise we'll read
		 * once and exit. We assume that in this case we are using
		 * level triggered interrupt and it will get raised again
		 * if/when there is more data.
		 */
		if (eeti->attn_gpio &&
		    !gpiod_get_value_cansleep(eeti->attn_gpio)) {
			break;
		}

		error = eeti_ts_read(eeti);
		if (error)
			break;

	} while (eeti->running && eeti->attn_gpio);

	mutex_unlock(&eeti->mutex);
	return IRQ_HANDLED;
}