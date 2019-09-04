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
struct mlx5_srq_attr {int /*<<< orphan*/  db_record; void* pd; void* lwm; void* page_offset; void* log_size; void* wqe_shift; void* log_page_size; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void* MLX5_GET (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET64 (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SRQ_FLAG_WQ_SIG ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  log_page_size ; 
 int /*<<< orphan*/  log_rq_stride ; 
 int /*<<< orphan*/  log_srq_size ; 
 int /*<<< orphan*/  lwm ; 
 int /*<<< orphan*/  page_offset ; 
 int /*<<< orphan*/  pd ; 
 int /*<<< orphan*/  wq_signature ; 

__attribute__((used)) static void get_srqc(void *srqc, struct mlx5_srq_attr *in)
{
	if (MLX5_GET(srqc, srqc, wq_signature))
		in->flags &= MLX5_SRQ_FLAG_WQ_SIG;
	in->log_page_size = MLX5_GET(srqc,   srqc, log_page_size);
	in->wqe_shift	  = MLX5_GET(srqc,   srqc, log_rq_stride);
	in->log_size	  = MLX5_GET(srqc,   srqc, log_srq_size);
	in->page_offset   = MLX5_GET(srqc,   srqc, page_offset);
	in->lwm		  = MLX5_GET(srqc,   srqc, lwm);
	in->pd		  = MLX5_GET(srqc,   srqc, pd);
	in->db_record	  = MLX5_GET64(srqc, srqc, dbr_addr);
}