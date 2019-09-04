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
typedef  int u32 ;
struct nes_qp {int dummy; } ;
struct nes_hw_qp_wqe {int /*<<< orphan*/  wqe_words; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_IWARP_SQ_WQE_COMP_CTX_HIGH_IDX ; 
 int /*<<< orphan*/  NES_IWARP_SQ_WQE_COMP_CTX_LOW_IDX ; 
 int /*<<< orphan*/  set_wqe_32bit_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ upper_32_bits (unsigned long) ; 

__attribute__((used)) static inline void
nes_fill_init_qp_wqe(struct nes_hw_qp_wqe *wqe, struct nes_qp *nesqp, u32 head)
{
	u32 value;
	value = ((u32)((unsigned long) nesqp)) | head;
	set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_COMP_CTX_HIGH_IDX,
			(u32)(upper_32_bits((unsigned long)(nesqp))));
	set_wqe_32bit_value(wqe->wqe_words, NES_IWARP_SQ_WQE_COMP_CTX_LOW_IDX, value);
}