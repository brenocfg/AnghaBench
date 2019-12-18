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
typedef  enum t3_wr_opcode { ____Placeholder_t3_wr_opcode } t3_wr_opcode ;
typedef  enum t3_rdma_opcode { ____Placeholder_t3_rdma_opcode } t3_rdma_opcode ;

/* Variables and functions */
 int T3_BIND_MW ; 
 int T3_BYPASS ; 
 int T3_FAST_REGISTER ; 
 int T3_LOCAL_INV ; 
 int T3_QP_MOD ; 
 int T3_RDMA_INIT ; 
 int T3_RDMA_WRITE ; 
 int T3_READ_REQ ; 
 int T3_SEND ; 
#define  T3_WR_BIND 136 
#define  T3_WR_BP 135 
#define  T3_WR_FASTREG 134 
#define  T3_WR_INIT 133 
#define  T3_WR_INV_STAG 132 
#define  T3_WR_QP_MOD 131 
#define  T3_WR_READ 130 
#define  T3_WR_SEND 129 
#define  T3_WR_WRITE 128 

__attribute__((used)) static inline enum t3_rdma_opcode wr2opcode(enum t3_wr_opcode wrop)
{
	switch (wrop) {
		case T3_WR_BP: return T3_BYPASS;
		case T3_WR_SEND: return T3_SEND;
		case T3_WR_WRITE: return T3_RDMA_WRITE;
		case T3_WR_READ: return T3_READ_REQ;
		case T3_WR_INV_STAG: return T3_LOCAL_INV;
		case T3_WR_BIND: return T3_BIND_MW;
		case T3_WR_INIT: return T3_RDMA_INIT;
		case T3_WR_QP_MOD: return T3_QP_MOD;
		case T3_WR_FASTREG: return T3_FAST_REGISTER;
		default: break;
	}
	return -1;
}