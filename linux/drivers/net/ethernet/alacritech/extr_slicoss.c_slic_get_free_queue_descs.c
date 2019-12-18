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

/* Variables and functions */

__attribute__((used)) static inline int slic_get_free_queue_descs(unsigned int put_idx,
					    unsigned int done_idx,
					    unsigned int qlen)
{
	if (put_idx >= done_idx)
		return (qlen - (put_idx - done_idx) - 1);
	return (done_idx - put_idx - 1);
}