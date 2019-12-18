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
struct eeti_ts {int running; int /*<<< orphan*/  mutex; scalar_t__ attn_gpio; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  eeti_ts_read (struct eeti_ts*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_get_value_cansleep (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eeti_ts_start(struct eeti_ts *eeti)
{
	mutex_lock(&eeti->mutex);

	eeti->running = true;
	enable_irq(eeti->client->irq);

	/*
	 * Kick the controller in case we are using edge interrupt and
	 * we missed our edge while interrupt was disabled. We expect
	 * the attention GPIO to be wired in this case.
	 */
	if (eeti->attn_gpio && gpiod_get_value_cansleep(eeti->attn_gpio))
		eeti_ts_read(eeti);

	mutex_unlock(&eeti->mutex);
}