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
typedef  unsigned long long uint32_t ;
struct mem_input {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPGV0_PIPE_ARBITRATION_CONTROL1 ; 
 int /*<<< orphan*/  DPGV1_PIPE_ARBITRATION_CONTROL1 ; 
 int /*<<< orphan*/  PIXEL_DURATION ; 
 unsigned long long dm_read_reg (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 unsigned long long mmDPGV0_PIPE_ARBITRATION_CONTROL1 ; 
 unsigned long long mmDPGV0_PIPE_ARBITRATION_CONTROL2 ; 
 unsigned long long mmDPGV1_PIPE_ARBITRATION_CONTROL1 ; 
 unsigned long long mmDPGV1_PIPE_ARBITRATION_CONTROL2 ; 
 int /*<<< orphan*/  set_reg_field_value (unsigned long long,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dce110_allocate_mem_input_v(
	struct mem_input *mi,
	uint32_t h_total,/* for current stream */
	uint32_t v_total,/* for current stream */
	uint32_t pix_clk_khz,/* for current stream */
	uint32_t total_stream_num)
{
	uint32_t addr;
	uint32_t value;
	uint32_t pix_dur;
	if (pix_clk_khz != 0) {
		addr = mmDPGV0_PIPE_ARBITRATION_CONTROL1;
		value = dm_read_reg(mi->ctx, addr);
		pix_dur = 1000000000ULL / pix_clk_khz;
		set_reg_field_value(
			value,
			pix_dur,
			DPGV0_PIPE_ARBITRATION_CONTROL1,
			PIXEL_DURATION);
		dm_write_reg(mi->ctx, addr, value);

		addr = mmDPGV1_PIPE_ARBITRATION_CONTROL1;
		value = dm_read_reg(mi->ctx, addr);
		pix_dur = 1000000000ULL / pix_clk_khz;
		set_reg_field_value(
			value,
			pix_dur,
			DPGV1_PIPE_ARBITRATION_CONTROL1,
			PIXEL_DURATION);
		dm_write_reg(mi->ctx, addr, value);

		addr = mmDPGV0_PIPE_ARBITRATION_CONTROL2;
		value = 0x4000800;
		dm_write_reg(mi->ctx, addr, value);

		addr = mmDPGV1_PIPE_ARBITRATION_CONTROL2;
		value = 0x4000800;
		dm_write_reg(mi->ctx, addr, value);
	}

}