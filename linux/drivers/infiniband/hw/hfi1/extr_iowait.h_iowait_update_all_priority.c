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
struct iowait {int /*<<< orphan*/ * wait; } ;

/* Variables and functions */
 size_t IOWAIT_IB_SE ; 
 size_t IOWAIT_TID_SE ; 
 int /*<<< orphan*/  iowait_update_priority (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iowait_update_all_priority(struct iowait *w)
{
	iowait_update_priority(&w->wait[IOWAIT_IB_SE]);
	iowait_update_priority(&w->wait[IOWAIT_TID_SE]);
}