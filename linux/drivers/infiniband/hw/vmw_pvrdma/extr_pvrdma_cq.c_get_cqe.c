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
struct pvrdma_cqe {int dummy; } ;
struct pvrdma_cq {scalar_t__ offset; int /*<<< orphan*/  pdir; } ;

/* Variables and functions */
 scalar_t__ pvrdma_page_dir_get_ptr (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline struct pvrdma_cqe *get_cqe(struct pvrdma_cq *cq, int i)
{
	return (struct pvrdma_cqe *)pvrdma_page_dir_get_ptr(
					&cq->pdir,
					cq->offset +
					sizeof(struct pvrdma_cqe) * i);
}