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
typedef  unsigned long long u64 ;

/* Variables and functions */
#define  NICVF_INTR_CQ 134 
 unsigned long long NICVF_INTR_CQ_SHIFT ; 
#define  NICVF_INTR_MBOX 133 
 unsigned long long NICVF_INTR_MBOX_SHIFT ; 
#define  NICVF_INTR_PKT_DROP 132 
 unsigned long long NICVF_INTR_PKT_DROP_SHIFT ; 
#define  NICVF_INTR_QS_ERR 131 
 unsigned long long NICVF_INTR_QS_ERR_SHIFT ; 
#define  NICVF_INTR_RBDR 130 
 unsigned long long NICVF_INTR_RBDR_SHIFT ; 
#define  NICVF_INTR_SQ 129 
 unsigned long long NICVF_INTR_SQ_SHIFT ; 
#define  NICVF_INTR_TCP_TIMER 128 
 unsigned long long NICVF_INTR_TCP_TIMER_SHIFT ; 

__attribute__((used)) static u64 nicvf_int_type_to_mask(int int_type, int q_idx)
{
	u64 reg_val;

	switch (int_type) {
	case NICVF_INTR_CQ:
		reg_val = ((1ULL << q_idx) << NICVF_INTR_CQ_SHIFT);
		break;
	case NICVF_INTR_SQ:
		reg_val = ((1ULL << q_idx) << NICVF_INTR_SQ_SHIFT);
		break;
	case NICVF_INTR_RBDR:
		reg_val = ((1ULL << q_idx) << NICVF_INTR_RBDR_SHIFT);
		break;
	case NICVF_INTR_PKT_DROP:
		reg_val = (1ULL << NICVF_INTR_PKT_DROP_SHIFT);
		break;
	case NICVF_INTR_TCP_TIMER:
		reg_val = (1ULL << NICVF_INTR_TCP_TIMER_SHIFT);
		break;
	case NICVF_INTR_MBOX:
		reg_val = (1ULL << NICVF_INTR_MBOX_SHIFT);
		break;
	case NICVF_INTR_QS_ERR:
		reg_val = (1ULL << NICVF_INTR_QS_ERR_SHIFT);
		break;
	default:
		reg_val = 0;
	}

	return reg_val;
}