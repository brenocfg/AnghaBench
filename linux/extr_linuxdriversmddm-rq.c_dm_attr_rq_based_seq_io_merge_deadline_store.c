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
struct mapped_device {unsigned int seq_rq_merge_deadline_usecs; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ DM_TYPE_REQUEST_BASED ; 
 size_t EINVAL ; 
 unsigned int MAX_SEQ_RQ_MERGE_DEADLINE_USECS ; 
 scalar_t__ dm_get_md_type (struct mapped_device*) ; 
 scalar_t__ kstrtouint (char const*,int,unsigned int*) ; 

ssize_t dm_attr_rq_based_seq_io_merge_deadline_store(struct mapped_device *md,
						     const char *buf, size_t count)
{
	unsigned deadline;

	if (dm_get_md_type(md) != DM_TYPE_REQUEST_BASED)
		return count;

	if (kstrtouint(buf, 10, &deadline))
		return -EINVAL;

	if (deadline > MAX_SEQ_RQ_MERGE_DEADLINE_USECS)
		deadline = MAX_SEQ_RQ_MERGE_DEADLINE_USECS;

	md->seq_rq_merge_deadline_usecs = deadline;

	return count;
}