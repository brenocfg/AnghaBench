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
struct tid_rdma_params {int max_len; int jkey; int max_write; int max_read; int qp; int urg; int timeout; } ;

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

__attribute__((used)) static void tid_rdma_opfn_decode(struct tid_rdma_params *p, u64 data)
{
	p->max_len = (((data >> TID_OPFN_MAX_LEN_SHIFT) &
		TID_OPFN_MAX_LEN_MASK) + 1) << PAGE_SHIFT;
	p->jkey = (data >> TID_OPFN_JKEY_SHIFT) & TID_OPFN_JKEY_MASK;
	p->max_write = (data >> TID_OPFN_MAX_WRITE_SHIFT) &
		TID_OPFN_MAX_WRITE_MASK;
	p->max_read = (data >> TID_OPFN_MAX_READ_SHIFT) &
		TID_OPFN_MAX_READ_MASK;
	p->qp =
		((((data >> TID_OPFN_QP_KDETH_SHIFT) & TID_OPFN_QP_KDETH_MASK)
			<< 16) |
		((data >> TID_OPFN_QP_CTXT_SHIFT) & TID_OPFN_QP_CTXT_MASK));
	p->urg = (data >> TID_OPFN_URG_SHIFT) & TID_OPFN_URG_MASK;
	p->timeout = (data >> TID_OPFN_TIMEOUT_SHIFT) & TID_OPFN_TIMEOUT_MASK;
}