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

/* Variables and functions */
 int IB_WC_COMP_SWAP ; 
 int IB_WC_FETCH_ADD ; 
 int IB_WC_LOCAL_INV ; 
 int IB_WC_MASKED_COMP_SWAP ; 
 int IB_WC_MASKED_FETCH_ADD ; 
 int IB_WC_RDMA_READ ; 
 int IB_WC_RDMA_WRITE ; 
 int IB_WC_RECV ; 
 int IB_WC_RECV_RDMA_WITH_IMM ; 
 int IB_WC_REG_MR ; 
 int IB_WC_SEND ; 
#define  PVRDMA_WC_COMP_SWAP 138 
#define  PVRDMA_WC_FAST_REG_MR 137 
#define  PVRDMA_WC_FETCH_ADD 136 
#define  PVRDMA_WC_LOCAL_INV 135 
#define  PVRDMA_WC_MASKED_COMP_SWAP 134 
#define  PVRDMA_WC_MASKED_FETCH_ADD 133 
#define  PVRDMA_WC_RDMA_READ 132 
#define  PVRDMA_WC_RDMA_WRITE 131 
#define  PVRDMA_WC_RECV 130 
#define  PVRDMA_WC_RECV_RDMA_WITH_IMM 129 
#define  PVRDMA_WC_SEND 128 

__attribute__((used)) static inline int pvrdma_wc_opcode_to_ib(unsigned int opcode)
{
	switch (opcode) {
	case PVRDMA_WC_SEND:
		return IB_WC_SEND;
	case PVRDMA_WC_RDMA_WRITE:
		return IB_WC_RDMA_WRITE;
	case PVRDMA_WC_RDMA_READ:
		return IB_WC_RDMA_READ;
	case PVRDMA_WC_COMP_SWAP:
		return IB_WC_COMP_SWAP;
	case PVRDMA_WC_FETCH_ADD:
		return IB_WC_FETCH_ADD;
	case PVRDMA_WC_LOCAL_INV:
		return IB_WC_LOCAL_INV;
	case PVRDMA_WC_FAST_REG_MR:
		return IB_WC_REG_MR;
	case PVRDMA_WC_MASKED_COMP_SWAP:
		return IB_WC_MASKED_COMP_SWAP;
	case PVRDMA_WC_MASKED_FETCH_ADD:
		return IB_WC_MASKED_FETCH_ADD;
	case PVRDMA_WC_RECV:
		return IB_WC_RECV;
	case PVRDMA_WC_RECV_RDMA_WITH_IMM:
		return IB_WC_RECV_RDMA_WITH_IMM;
	default:
		return IB_WC_SEND;
	}
}