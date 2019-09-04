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
typedef  unsigned int u32 ;

/* Variables and functions */
#define  CTXT_EGRESS 130 
#define  CTXT_FLM 129 
#define  CTXT_INGRESS 128 

__attribute__((used)) static int cudbg_sge_ctxt_check_valid(u32 *buf, int type)
{
	int index, bit, bit_pos = 0;

	switch (type) {
	case CTXT_EGRESS:
		bit_pos = 176;
		break;
	case CTXT_INGRESS:
		bit_pos = 141;
		break;
	case CTXT_FLM:
		bit_pos = 89;
		break;
	}
	index = bit_pos / 32;
	bit =  bit_pos % 32;
	return buf[index] & (1U << bit);
}