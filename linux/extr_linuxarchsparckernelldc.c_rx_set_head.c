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
struct ldc_channel {unsigned long rx_head; } ;

/* Variables and functions */
 int LDC_ABORT (struct ldc_channel*) ; 
 int __set_rx_head (struct ldc_channel*,unsigned long) ; 

__attribute__((used)) static int rx_set_head(struct ldc_channel *lp, unsigned long head)
{
	int err = __set_rx_head(lp, head);

	if (err < 0)
		return LDC_ABORT(lp);

	lp->rx_head = head;
	return 0;
}