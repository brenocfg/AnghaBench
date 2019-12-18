#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mem_input {int dummy; } ;
struct TYPE_2__ {int single_head_rdreq_dmif_limit; } ;
struct dce_mem_input {TYPE_1__ wa; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMIF_BUFFERS_ALLOCATED ; 
 int /*<<< orphan*/  DMIF_BUFFERS_ALLOCATION_COMPLETED ; 
 int /*<<< orphan*/  DMIF_BUFFER_CONTROL ; 
 int /*<<< orphan*/  DPG_PIPE_ARBITRATION_CONTROL1 ; 
 int /*<<< orphan*/  ENABLE ; 
 int /*<<< orphan*/  MC_HUB_RDREQ_DMIF_LIMIT ; 
 int /*<<< orphan*/  PIXEL_DURATION ; 
 int REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int const,int) ; 
 struct dce_mem_input* TO_DCE_MEM_INPUT (struct mem_input*) ; 
 int const get_dmif_switch_time_us (int,int,int) ; 

__attribute__((used)) static void dce_mi_allocate_dmif(
	struct mem_input *mi,
	uint32_t h_total,
	uint32_t v_total,
	uint32_t pix_clk_khz,
	uint32_t total_stream_num)
{
	struct dce_mem_input *dce_mi = TO_DCE_MEM_INPUT(mi);
	const uint32_t retry_delay = 10;
	uint32_t retry_count = get_dmif_switch_time_us(
			h_total,
			v_total,
			pix_clk_khz) / retry_delay;

	uint32_t pix_dur;
	uint32_t buffers_allocated;
	uint32_t dmif_buffer_control;

	dmif_buffer_control = REG_GET(DMIF_BUFFER_CONTROL,
			DMIF_BUFFERS_ALLOCATED, &buffers_allocated);

	if (buffers_allocated == 2)
		return;

	REG_SET(DMIF_BUFFER_CONTROL, dmif_buffer_control,
			DMIF_BUFFERS_ALLOCATED, 2);

	REG_WAIT(DMIF_BUFFER_CONTROL,
			DMIF_BUFFERS_ALLOCATION_COMPLETED, 1,
			retry_delay, retry_count);

	if (pix_clk_khz != 0) {
		pix_dur = 1000000000ULL / pix_clk_khz;

		REG_UPDATE(DPG_PIPE_ARBITRATION_CONTROL1,
			PIXEL_DURATION, pix_dur);
	}

	if (dce_mi->wa.single_head_rdreq_dmif_limit) {
		uint32_t eanble =  (total_stream_num > 1) ? 0 :
				dce_mi->wa.single_head_rdreq_dmif_limit;

		REG_UPDATE(MC_HUB_RDREQ_DMIF_LIMIT,
				ENABLE, eanble);
	}
}