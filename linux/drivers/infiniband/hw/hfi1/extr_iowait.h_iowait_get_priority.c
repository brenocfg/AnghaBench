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
struct iowait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowait_init_priority (struct iowait*) ; 
 int /*<<< orphan*/  iowait_update_all_priority (struct iowait*) ; 

__attribute__((used)) static inline void iowait_get_priority(struct iowait *w)
{
	iowait_init_priority(w);
	iowait_update_all_priority(w);
}