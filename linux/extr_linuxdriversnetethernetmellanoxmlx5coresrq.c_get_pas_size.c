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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx5_srq_attr {int log_page_size; int log_size; int wqe_shift; int page_offset; } ;

/* Variables and functions */

__attribute__((used)) static int get_pas_size(struct mlx5_srq_attr *in)
{
	u32 log_page_size = in->log_page_size + 12;
	u32 log_srq_size  = in->log_size;
	u32 log_rq_stride = in->wqe_shift;
	u32 page_offset   = in->page_offset;
	u32 po_quanta	  = 1 << (log_page_size - 6);
	u32 rq_sz	  = 1 << (log_srq_size + 4 + log_rq_stride);
	u32 page_size	  = 1 << log_page_size;
	u32 rq_sz_po      = rq_sz + (page_offset * po_quanta);
	u32 rq_num_pas	  = (rq_sz_po + page_size - 1) / page_size;

	return rq_num_pas * sizeof(u64);
}