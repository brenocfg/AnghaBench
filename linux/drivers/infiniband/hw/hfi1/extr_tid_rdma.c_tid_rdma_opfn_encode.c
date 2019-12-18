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
struct tid_rdma_params {int max_len; scalar_t__ max_write; scalar_t__ max_read; scalar_t__ jkey; scalar_t__ urg; scalar_t__ timeout; scalar_t__ qp; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int TID_OPFN_JKEY_MASK ; 
 int TID_OPFN_JKEY_SHIFT ; 
 int TID_OPFN_MAX_LEN_MASK ; 
 int TID_OPFN_MAX_LEN_SHIFT ; 
 int TID_OPFN_MAX_READ_MASK ; 
 int TID_OPFN_MAX_READ_SHIFT ; 
 int TID_OPFN_MAX_WRITE_MASK ; 
 int TID_OPFN_MAX_WRITE_SHIFT ; 
 int TID_OPFN_QP_CTXT_MASK ; 
 int TID_OPFN_QP_CTXT_SHIFT ; 
 int TID_OPFN_QP_KDETH_MASK ; 
 int TID_OPFN_QP_KDETH_SHIFT ; 
 int TID_OPFN_TIMEOUT_MASK ; 
 int TID_OPFN_TIMEOUT_SHIFT ; 
 int TID_OPFN_URG_MASK ; 
 int TID_OPFN_URG_SHIFT ; 

__attribute__((used)) static u64 tid_rdma_opfn_encode(struct tid_rdma_params *p)
{
	return
		(((u64)p->qp & TID_OPFN_QP_CTXT_MASK) <<
			TID_OPFN_QP_CTXT_SHIFT) |
		((((u64)p->qp >> 16) & TID_OPFN_QP_KDETH_MASK) <<
			TID_OPFN_QP_KDETH_SHIFT) |
		(((u64)((p->max_len >> PAGE_SHIFT) - 1) &
			TID_OPFN_MAX_LEN_MASK) << TID_OPFN_MAX_LEN_SHIFT) |
		(((u64)p->timeout & TID_OPFN_TIMEOUT_MASK) <<
			TID_OPFN_TIMEOUT_SHIFT) |
		(((u64)p->urg & TID_OPFN_URG_MASK) << TID_OPFN_URG_SHIFT) |
		(((u64)p->jkey & TID_OPFN_JKEY_MASK) << TID_OPFN_JKEY_SHIFT) |
		(((u64)p->max_read & TID_OPFN_MAX_READ_MASK) <<
			TID_OPFN_MAX_READ_SHIFT) |
		(((u64)p->max_write & TID_OPFN_MAX_WRITE_MASK) <<
			TID_OPFN_MAX_WRITE_SHIFT);
}