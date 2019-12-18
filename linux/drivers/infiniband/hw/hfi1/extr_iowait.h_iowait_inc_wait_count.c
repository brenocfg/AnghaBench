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
typedef  scalar_t__ u16 ;
struct iowait_work {TYPE_1__* iow; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  tx_count; } ;

/* Variables and functions */

__attribute__((used)) static inline void iowait_inc_wait_count(struct iowait_work *w, u16 n)
{
	if (!w)
		return;
	w->iow->tx_count++;
	w->iow->count += n;
}