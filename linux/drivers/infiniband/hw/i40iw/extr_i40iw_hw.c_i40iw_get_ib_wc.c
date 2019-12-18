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
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
typedef  enum i40iw_flush_opcode { ____Placeholder_i40iw_flush_opcode } i40iw_flush_opcode ;

/* Variables and functions */
#define  FLUSH_FATAL_ERR 134 
#define  FLUSH_GENERAL_ERR 133 
#define  FLUSH_LOC_LEN_ERR 132 
#define  FLUSH_LOC_QP_OP_ERR 131 
#define  FLUSH_PROT_ERR 130 
#define  FLUSH_REM_ACCESS_ERR 129 
#define  FLUSH_REM_OP_ERR 128 
 int IB_WC_FATAL_ERR ; 
 int IB_WC_GENERAL_ERR ; 
 int IB_WC_LOC_LEN_ERR ; 
 int IB_WC_LOC_PROT_ERR ; 
 int IB_WC_LOC_QP_OP_ERR ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_OP_ERR ; 

__attribute__((used)) static enum ib_wc_status i40iw_get_ib_wc(enum i40iw_flush_opcode opcode)
{
	switch (opcode) {
	case FLUSH_PROT_ERR:
		return IB_WC_LOC_PROT_ERR;
	case FLUSH_REM_ACCESS_ERR:
		return IB_WC_REM_ACCESS_ERR;
	case FLUSH_LOC_QP_OP_ERR:
		return IB_WC_LOC_QP_OP_ERR;
	case FLUSH_REM_OP_ERR:
		return IB_WC_REM_OP_ERR;
	case FLUSH_LOC_LEN_ERR:
		return IB_WC_LOC_LEN_ERR;
	case FLUSH_GENERAL_ERR:
		return IB_WC_GENERAL_ERR;
	case FLUSH_FATAL_ERR:
	default:
		return IB_WC_FATAL_ERR;
	}
}