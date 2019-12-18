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
typedef  int u16 ;
struct io_register {int start_bit; int end_bit; int io_addr; } ;

/* Variables and functions */
 int BIT0 ; 
 int VIACR ; 
 int VIASR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int,int,int,int) ; 

void viafb_load_reg(int timing_value, int viafb_load_reg_num,
	struct io_register *reg,
	      int io_type)
{
	int reg_mask;
	int bit_num = 0;
	int data;
	int i, j;
	int shift_next_reg;
	int start_index, end_index, cr_index;
	u16 get_bit;

	for (i = 0; i < viafb_load_reg_num; i++) {
		reg_mask = 0;
		data = 0;
		start_index = reg[i].start_bit;
		end_index = reg[i].end_bit;
		cr_index = reg[i].io_addr;

		shift_next_reg = bit_num;
		for (j = start_index; j <= end_index; j++) {
			/*if (bit_num==8) timing_value = timing_value >>8; */
			reg_mask = reg_mask | (BIT0 << j);
			get_bit = (timing_value & (BIT0 << bit_num));
			data =
			    data | ((get_bit >> shift_next_reg) << start_index);
			bit_num++;
		}
		if (io_type == VIACR)
			viafb_write_reg_mask(cr_index, VIACR, data, reg_mask);
		else
			viafb_write_reg_mask(cr_index, VIASR, data, reg_mask);
	}

}