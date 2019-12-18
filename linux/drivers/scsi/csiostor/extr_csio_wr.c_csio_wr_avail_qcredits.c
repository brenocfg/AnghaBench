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
typedef  scalar_t__ uint32_t ;
struct csio_q {scalar_t__ pidx; scalar_t__ cidx; scalar_t__ credits; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t
csio_wr_avail_qcredits(struct csio_q *q)
{
	if (q->pidx > q->cidx)
		return q->pidx - q->cidx;
	else if (q->cidx > q->pidx)
		return q->credits - (q->cidx - q->pidx);
	else
		return 0;	/* cidx == pidx, empty queue */
}