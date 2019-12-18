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
typedef  size_t uint16_t ;
struct lpfc_queue {void** q_pgs; size_t entry_cnt_per_pg; size_t entry_size; } ;

/* Variables and functions */

__attribute__((used)) static inline void *lpfc_sli4_qe(struct lpfc_queue *q, uint16_t idx)
{
	return q->q_pgs[idx / q->entry_cnt_per_pg] +
		(q->entry_size * (idx % q->entry_cnt_per_pg));
}