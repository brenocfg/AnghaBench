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
struct fusb300_ep {scalar_t__ epnum; struct fusb300* fusb300; } ;
struct fusb300 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FUSB300_IGER0_EEPn_FIFO_INT (scalar_t__) ; 
 int /*<<< orphan*/  FUSB300_OFFSET_IGER0 ; 
 int /*<<< orphan*/  fusb300_disable_bit (struct fusb300*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int disable_fifo_int(struct fusb300_ep *ep)
{
	struct fusb300 *fusb300 = ep->fusb300;

	if (ep->epnum) {
		fusb300_disable_bit(fusb300, FUSB300_OFFSET_IGER0,
			FUSB300_IGER0_EEPn_FIFO_INT(ep->epnum));
	} else {
		pr_err("can't disable_fifo_int ep0\n");
		return -EINVAL;
	}

	return 0;
}