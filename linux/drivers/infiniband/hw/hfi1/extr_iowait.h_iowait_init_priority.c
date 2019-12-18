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
struct iowait {int /*<<< orphan*/  (* init_priority ) (struct iowait*) ;scalar_t__ priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct iowait*) ; 

__attribute__((used)) static inline void iowait_init_priority(struct iowait *w)
{
	w->priority = 0;
	if (w->init_priority)
		w->init_priority(w);
}