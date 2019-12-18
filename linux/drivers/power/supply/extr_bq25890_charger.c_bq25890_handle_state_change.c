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
struct bq25890_state {int /*<<< orphan*/  online; } ;
struct bq25890_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; struct bq25890_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_CONV_START ; 
 int bq25890_field_write (struct bq25890_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bq25890_handle_state_change(struct bq25890_device *bq,
					struct bq25890_state *new_state)
{
	int ret;
	struct bq25890_state old_state;

	mutex_lock(&bq->lock);
	old_state = bq->state;
	mutex_unlock(&bq->lock);

	if (!new_state->online) {			     /* power removed */
		/* disable ADC */
		ret = bq25890_field_write(bq, F_CONV_START, 0);
		if (ret < 0)
			goto error;
	} else if (!old_state.online) {			    /* power inserted */
		/* enable ADC, to have control of charge current/voltage */
		ret = bq25890_field_write(bq, F_CONV_START, 1);
		if (ret < 0)
			goto error;
	}

	return;

error:
	dev_err(bq->dev, "Error communicating with the chip.\n");
}