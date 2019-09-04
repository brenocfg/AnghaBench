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
struct vas_rx_win_attr {scalar_t__ rx_fifo_size; scalar_t__ wcreds_max; scalar_t__ intr_disable; scalar_t__ rx_fifo; scalar_t__ user_win; scalar_t__ notify_disable; scalar_t__ fault_win; scalar_t__ notify_early; scalar_t__ nx_win; } ;
typedef  enum vas_cop_type { ____Placeholder_vas_cop_type } vas_cop_type ;

/* Variables and functions */
 int VAS_COP_TYPE_FTW ; 
 int VAS_COP_TYPE_MAX ; 
 scalar_t__ VAS_RX_FIFO_SIZE_MAX ; 
 scalar_t__ VAS_RX_FIFO_SIZE_MIN ; 
 scalar_t__ VAS_RX_WCREDS_MAX ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool rx_win_args_valid(enum vas_cop_type cop,
			struct vas_rx_win_attr *attr)
{
	pr_debug("Rxattr: fault %d, notify %d, intr %d, early %d, fifo %d\n",
			attr->fault_win, attr->notify_disable,
			attr->intr_disable, attr->notify_early,
			attr->rx_fifo_size);

	if (cop >= VAS_COP_TYPE_MAX)
		return false;

	if (cop != VAS_COP_TYPE_FTW &&
				attr->rx_fifo_size < VAS_RX_FIFO_SIZE_MIN)
		return false;

	if (attr->rx_fifo_size > VAS_RX_FIFO_SIZE_MAX)
		return false;

	if (attr->wcreds_max > VAS_RX_WCREDS_MAX)
		return false;

	if (attr->nx_win) {
		/* cannot be fault or user window if it is nx */
		if (attr->fault_win || attr->user_win)
			return false;
		/*
		 * Section 3.1.4.32: NX Windows must not disable notification,
		 *	and must not enable interrupts or early notification.
		 */
		if (attr->notify_disable || !attr->intr_disable ||
				attr->notify_early)
			return false;
	} else if (attr->fault_win) {
		/* cannot be both fault and user window */
		if (attr->user_win)
			return false;

		/*
		 * Section 3.1.4.32: Fault windows must disable notification
		 *	but not interrupts.
		 */
		if (!attr->notify_disable || attr->intr_disable)
			return false;

	} else if (attr->user_win) {
		/*
		 * User receive windows are only for fast-thread-wakeup
		 * (FTW). They don't need a FIFO and must disable interrupts
		 */
		if (attr->rx_fifo || attr->rx_fifo_size || !attr->intr_disable)
			return false;
	} else {
		/* Rx window must be one of NX or Fault or User window. */
		return false;
	}

	return true;
}