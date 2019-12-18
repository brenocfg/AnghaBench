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
struct ep_data {int state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 unsigned int O_NONBLOCK ; 
#define  STATE_EP_ENABLED 130 
#define  STATE_EP_READY 129 
#define  STATE_EP_UNBOUND 128 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,struct ep_data*,int) ; 
 int /*<<< orphan*/  shortname ; 

__attribute__((used)) static int
get_ready_ep (unsigned f_flags, struct ep_data *epdata, bool is_write)
{
	int	val;

	if (f_flags & O_NONBLOCK) {
		if (!mutex_trylock(&epdata->lock))
			goto nonblock;
		if (epdata->state != STATE_EP_ENABLED &&
		    (!is_write || epdata->state != STATE_EP_READY)) {
			mutex_unlock(&epdata->lock);
nonblock:
			val = -EAGAIN;
		} else
			val = 0;
		return val;
	}

	val = mutex_lock_interruptible(&epdata->lock);
	if (val < 0)
		return val;

	switch (epdata->state) {
	case STATE_EP_ENABLED:
		return 0;
	case STATE_EP_READY:			/* not configured yet */
		if (is_write)
			return 0;
		// FALLTHRU
	case STATE_EP_UNBOUND:			/* clean disconnect */
		break;
	// case STATE_EP_DISABLED:		/* "can't happen" */
	default:				/* error! */
		pr_debug ("%s: ep %p not available, state %d\n",
				shortname, epdata, epdata->state);
	}
	mutex_unlock(&epdata->lock);
	return -ENODEV;
}