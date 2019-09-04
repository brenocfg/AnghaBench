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
struct elevator_queue {struct bfq_data* elevator_data; } ;
struct bfq_data {unsigned long strict_guarantees; int bfq_slice_idle; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int NSEC_PER_MSEC ; 
 int bfq_var_store (unsigned long*,char const*) ; 

__attribute__((used)) static ssize_t bfq_strict_guarantees_store(struct elevator_queue *e,
				     const char *page, size_t count)
{
	struct bfq_data *bfqd = e->elevator_data;
	unsigned long __data;
	int ret;

	ret = bfq_var_store(&__data, (page));
	if (ret)
		return ret;

	if (__data > 1)
		__data = 1;
	if (!bfqd->strict_guarantees && __data == 1
	    && bfqd->bfq_slice_idle < 8 * NSEC_PER_MSEC)
		bfqd->bfq_slice_idle = 8 * NSEC_PER_MSEC;

	bfqd->strict_guarantees = __data;

	return count;
}