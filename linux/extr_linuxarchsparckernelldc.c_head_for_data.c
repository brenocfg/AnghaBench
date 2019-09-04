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
struct TYPE_2__ {scalar_t__ mode; } ;
struct ldc_channel {unsigned long tx_acked; unsigned long tx_head; TYPE_1__ cfg; } ;

/* Variables and functions */
 scalar_t__ LDC_MODE_STREAM ; 

__attribute__((used)) static unsigned long head_for_data(struct ldc_channel *lp)
{
	if (lp->cfg.mode == LDC_MODE_STREAM)
		return lp->tx_acked;
	return lp->tx_head;
}