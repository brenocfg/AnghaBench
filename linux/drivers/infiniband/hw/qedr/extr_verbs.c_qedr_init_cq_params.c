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
struct qedr_ucontext {int /*<<< orphan*/  dpi; } ;
struct qedr_dev {int /*<<< orphan*/  dpi; } ;
struct qedr_cq {int dummy; } ;
struct qed_rdma_create_cq_in_params {int cnq_id; int cq_size; int pbl_num_pages; scalar_t__ pbl_two_level; int /*<<< orphan*/  pbl_ptr; int /*<<< orphan*/  dpi; int /*<<< orphan*/  cq_handle_lo; int /*<<< orphan*/  cq_handle_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (uintptr_t) ; 
 int /*<<< orphan*/  memset (struct qed_rdma_create_cq_in_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upper_32_bits (uintptr_t) ; 

__attribute__((used)) static inline void qedr_init_cq_params(struct qedr_cq *cq,
				       struct qedr_ucontext *ctx,
				       struct qedr_dev *dev, int vector,
				       int chain_entries, int page_cnt,
				       u64 pbl_ptr,
				       struct qed_rdma_create_cq_in_params
				       *params)
{
	memset(params, 0, sizeof(*params));
	params->cq_handle_hi = upper_32_bits((uintptr_t)cq);
	params->cq_handle_lo = lower_32_bits((uintptr_t)cq);
	params->cnq_id = vector;
	params->cq_size = chain_entries - 1;
	params->dpi = (ctx) ? ctx->dpi : dev->dpi;
	params->pbl_num_pages = page_cnt;
	params->pbl_ptr = pbl_ptr;
	params->pbl_two_level = 0;
}