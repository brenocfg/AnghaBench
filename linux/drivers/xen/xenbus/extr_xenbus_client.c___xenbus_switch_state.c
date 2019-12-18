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
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {int state; int /*<<< orphan*/  nodename; } ;
typedef  enum xenbus_state { ____Placeholder_xenbus_state } xenbus_state ;

/* Variables and functions */
 int EAGAIN ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,int) ; 
 int xenbus_scanf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  xenbus_switch_fatal (struct xenbus_device*,int,int,char*) ; 
 int xenbus_transaction_end (struct xenbus_transaction,int) ; 
 int xenbus_transaction_start (struct xenbus_transaction*) ; 

__attribute__((used)) static int
__xenbus_switch_state(struct xenbus_device *dev,
		      enum xenbus_state state, int depth)
{
	/* We check whether the state is currently set to the given value, and
	   if not, then the state is set.  We don't want to unconditionally
	   write the given state, because we don't want to fire watches
	   unnecessarily.  Furthermore, if the node has gone, we don't write
	   to it, as the device will be tearing down, and we don't want to
	   resurrect that directory.

	   Note that, because of this cached value of our state, this
	   function will not take a caller's Xenstore transaction
	   (something it was trying to in the past) because dev->state
	   would not get reset if the transaction was aborted.
	 */

	struct xenbus_transaction xbt;
	int current_state;
	int err, abort;

	if (state == dev->state)
		return 0;

again:
	abort = 1;

	err = xenbus_transaction_start(&xbt);
	if (err) {
		xenbus_switch_fatal(dev, depth, err, "starting transaction");
		return 0;
	}

	err = xenbus_scanf(xbt, dev->nodename, "state", "%d", &current_state);
	if (err != 1)
		goto abort;

	err = xenbus_printf(xbt, dev->nodename, "state", "%d", state);
	if (err) {
		xenbus_switch_fatal(dev, depth, err, "writing new state");
		goto abort;
	}

	abort = 0;
abort:
	err = xenbus_transaction_end(xbt, abort);
	if (err) {
		if (err == -EAGAIN && !abort)
			goto again;
		xenbus_switch_fatal(dev, depth, err, "ending transaction");
	} else
		dev->state = state;

	return 0;
}