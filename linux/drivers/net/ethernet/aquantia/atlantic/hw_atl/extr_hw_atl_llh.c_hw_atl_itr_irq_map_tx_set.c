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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aq_hw_write_reg_bit (struct aq_hw_s*,int,int,int,int) ; 

void hw_atl_itr_irq_map_tx_set(struct aq_hw_s *aq_hw, u32 irq_map_tx, u32 tx)
{
/* register address for bitfield imr_tx{t}[4:0] */
	static u32 itr_imr_txt_adr[32] = {
			0x00002100U, 0x00002100U, 0x00002104U, 0x00002104U,
			0x00002108U, 0x00002108U, 0x0000210CU, 0x0000210CU,
			0x00002110U, 0x00002110U, 0x00002114U, 0x00002114U,
			0x00002118U, 0x00002118U, 0x0000211CU, 0x0000211CU,
			0x00002120U, 0x00002120U, 0x00002124U, 0x00002124U,
			0x00002128U, 0x00002128U, 0x0000212CU, 0x0000212CU,
			0x00002130U, 0x00002130U, 0x00002134U, 0x00002134U,
			0x00002138U, 0x00002138U, 0x0000213CU, 0x0000213CU
		};

/* bitmask for bitfield imr_tx{t}[4:0] */
	static u32 itr_imr_txt_msk[32] = {
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U,
			0x1f000000U, 0x001F0000U, 0x1F000000U, 0x001F0000U
		};

/* lower bit position of bitfield imr_tx{t}[4:0] */
	static u32 itr_imr_txt_shift[32] = {
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U,
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U,
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U,
			24U, 16U, 24U, 16U, 24U, 16U, 24U, 16U
		};

	aq_hw_write_reg_bit(aq_hw, itr_imr_txt_adr[tx],
			    itr_imr_txt_msk[tx],
			    itr_imr_txt_shift[tx],
			    irq_map_tx);
}