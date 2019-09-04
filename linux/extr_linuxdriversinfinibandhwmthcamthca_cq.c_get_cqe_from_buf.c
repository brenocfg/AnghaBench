#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mthca_cqe {int dummy; } ;
struct TYPE_4__ {struct mthca_cqe* buf; } ;
struct TYPE_6__ {TYPE_2__* page_list; TYPE_1__ direct; } ;
struct mthca_cq_buf {TYPE_3__ queue; scalar_t__ is_direct; } ;
struct TYPE_5__ {struct mthca_cqe* buf; } ;

/* Variables and functions */
 int MTHCA_CQ_ENTRY_SIZE ; 
 int PAGE_SIZE ; 

__attribute__((used)) static inline struct mthca_cqe *get_cqe_from_buf(struct mthca_cq_buf *buf,
						 int entry)
{
	if (buf->is_direct)
		return buf->queue.direct.buf + (entry * MTHCA_CQ_ENTRY_SIZE);
	else
		return buf->queue.page_list[entry * MTHCA_CQ_ENTRY_SIZE / PAGE_SIZE].buf
			+ (entry * MTHCA_CQ_ENTRY_SIZE) % PAGE_SIZE;
}