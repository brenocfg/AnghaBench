#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct devfreq_freqs {unsigned long old; unsigned long new; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct devfreq {unsigned long previous_freq; TYPE_3__ dev; TYPE_2__* profile; int /*<<< orphan*/  min_freq; int /*<<< orphan*/  scaling_min_freq; int /*<<< orphan*/  max_freq; int /*<<< orphan*/  scaling_max_freq; TYPE_1__* governor; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int (* target ) (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_cur_freq ) (int /*<<< orphan*/ ,unsigned long*) ;} ;
struct TYPE_4__ {int (* get_target_freq ) (struct devfreq*,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_FLAG_LEAST_UPPER_BOUND ; 
 int /*<<< orphan*/  DEVFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  DEVFREQ_PRECHANGE ; 
 int EINVAL ; 
 unsigned long MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devfreq_notify_transition (struct devfreq*,struct devfreq_freqs*,int /*<<< orphan*/ ) ; 
 scalar_t__ devfreq_update_status (struct devfreq*,unsigned long) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct devfreq*,unsigned long*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,unsigned long*) ; 
 int stub3 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 

int update_devfreq(struct devfreq *devfreq)
{
	struct devfreq_freqs freqs;
	unsigned long freq, cur_freq, min_freq, max_freq;
	int err = 0;
	u32 flags = 0;

	if (!mutex_is_locked(&devfreq->lock)) {
		WARN(true, "devfreq->lock must be locked by the caller.\n");
		return -EINVAL;
	}

	if (!devfreq->governor)
		return -EINVAL;

	/* Reevaluate the proper frequency */
	err = devfreq->governor->get_target_freq(devfreq, &freq);
	if (err)
		return err;

	/*
	 * Adjust the frequency with user freq, QoS and available freq.
	 *
	 * List from the highest priority
	 * max_freq
	 * min_freq
	 */
	max_freq = MIN(devfreq->scaling_max_freq, devfreq->max_freq);
	min_freq = MAX(devfreq->scaling_min_freq, devfreq->min_freq);

	if (min_freq && freq < min_freq) {
		freq = min_freq;
		flags &= ~DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use GLB */
	}
	if (max_freq && freq > max_freq) {
		freq = max_freq;
		flags |= DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use LUB */
	}

	if (devfreq->profile->get_cur_freq)
		devfreq->profile->get_cur_freq(devfreq->dev.parent, &cur_freq);
	else
		cur_freq = devfreq->previous_freq;

	freqs.old = cur_freq;
	freqs.new = freq;
	devfreq_notify_transition(devfreq, &freqs, DEVFREQ_PRECHANGE);

	err = devfreq->profile->target(devfreq->dev.parent, &freq, flags);
	if (err) {
		freqs.new = cur_freq;
		devfreq_notify_transition(devfreq, &freqs, DEVFREQ_POSTCHANGE);
		return err;
	}

	freqs.new = freq;
	devfreq_notify_transition(devfreq, &freqs, DEVFREQ_POSTCHANGE);

	if (devfreq_update_status(devfreq, freq))
		dev_err(&devfreq->dev,
			"Couldn't update frequency transition information.\n");

	devfreq->previous_freq = freq;
	return err;
}