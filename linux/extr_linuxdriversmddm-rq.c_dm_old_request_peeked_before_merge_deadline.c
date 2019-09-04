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
typedef  int u64 ;
struct mapped_device {int /*<<< orphan*/  last_rq_start_time; scalar_t__ seq_rq_merge_deadline_usecs; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  ktime_add_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 

__attribute__((used)) static bool dm_old_request_peeked_before_merge_deadline(struct mapped_device *md)
{
	ktime_t kt_deadline;

	if (!md->seq_rq_merge_deadline_usecs)
		return false;

	kt_deadline = ns_to_ktime((u64)md->seq_rq_merge_deadline_usecs * NSEC_PER_USEC);
	kt_deadline = ktime_add_safe(md->last_rq_start_time, kt_deadline);

	return !ktime_after(ktime_get(), kt_deadline);
}