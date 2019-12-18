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
struct iowait_work {int dummy; } ;
struct iowait {struct iowait_work* wait; } ;

/* Variables and functions */
 size_t IOWAIT_TID_SE ; 

__attribute__((used)) static inline struct iowait_work *iowait_get_tid_work(struct iowait *w)
{
	return &w->wait[IOWAIT_TID_SE];
}