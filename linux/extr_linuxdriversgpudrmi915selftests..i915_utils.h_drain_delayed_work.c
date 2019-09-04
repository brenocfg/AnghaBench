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
struct delayed_work {int dummy; } ;

/* Variables and functions */
 scalar_t__ delayed_work_pending (struct delayed_work*) ; 
 scalar_t__ flush_delayed_work (struct delayed_work*) ; 

__attribute__((used)) static inline void drain_delayed_work(struct delayed_work *dw)
{
	do {
		while (flush_delayed_work(dw))
			;
	} while (delayed_work_pending(dw));
}