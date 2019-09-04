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
typedef  unsigned long long u64 ;
struct request_queue {int dummy; } ;

/* Variables and functions */
 scalar_t__ blk_queue_nonrot (struct request_queue*) ; 

u64 wbt_default_latency_nsec(struct request_queue *q)
{
	/*
	 * We default to 2msec for non-rotational storage, and 75msec
	 * for rotational storage.
	 */
	if (blk_queue_nonrot(q))
		return 2000000ULL;
	else
		return 75000000ULL;
}