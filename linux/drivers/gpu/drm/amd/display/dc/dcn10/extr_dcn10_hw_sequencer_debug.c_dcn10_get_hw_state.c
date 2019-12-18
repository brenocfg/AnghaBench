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
struct dc {int dummy; } ;

/* Variables and functions */
 unsigned int dcn10_get_clock_states (struct dc*,char*,unsigned int) ; 
 unsigned int dcn10_get_cm_states (struct dc*,char*,unsigned int) ; 
 unsigned int dcn10_get_dlg_states (struct dc*,char*,unsigned int) ; 
 unsigned int dcn10_get_hubbub_state (struct dc*,char*,unsigned int) ; 
 unsigned int dcn10_get_hubp_states (struct dc*,char*,unsigned int,unsigned int) ; 
 unsigned int dcn10_get_mpcc_states (struct dc*,char*,unsigned int) ; 
 unsigned int dcn10_get_otg_states (struct dc*,char*,unsigned int) ; 
 unsigned int dcn10_get_rq_states (struct dc*,char*,unsigned int) ; 
 unsigned int dcn10_get_ttu_states (struct dc*,char*,unsigned int) ; 

void dcn10_get_hw_state(struct dc *dc, char *pBuf, unsigned int bufSize, unsigned int mask)
{
	/*
	 *  Mask Format
	 *  Bit 0 - 15: Hardware block mask
	 *  Bit 15: 1 = Invariant Only, 0 = All
	 */
	const unsigned int DC_HW_STATE_MASK_HUBBUB			= 0x1;
	const unsigned int DC_HW_STATE_MASK_HUBP			= 0x2;
	const unsigned int DC_HW_STATE_MASK_RQ				= 0x4;
	const unsigned int DC_HW_STATE_MASK_DLG				= 0x8;
	const unsigned int DC_HW_STATE_MASK_TTU				= 0x10;
	const unsigned int DC_HW_STATE_MASK_CM				= 0x20;
	const unsigned int DC_HW_STATE_MASK_MPCC			= 0x40;
	const unsigned int DC_HW_STATE_MASK_OTG				= 0x80;
	const unsigned int DC_HW_STATE_MASK_CLOCKS			= 0x100;
	const unsigned int DC_HW_STATE_INVAR_ONLY			= 0x8000;

	unsigned int chars_printed = 0;
	unsigned int remaining_buf_size = bufSize;

	if (mask == 0x0)
		mask = 0xFFFF; // Default, capture all, invariant only

	if ((mask & DC_HW_STATE_MASK_HUBBUB) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_hubbub_state(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_HUBP) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_hubp_states(dc, pBuf, remaining_buf_size, mask & DC_HW_STATE_INVAR_ONLY);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_RQ) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_rq_states(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_DLG) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_dlg_states(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_TTU) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_ttu_states(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_CM) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_cm_states(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_MPCC) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_mpcc_states(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_OTG) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_otg_states(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}

	if ((mask & DC_HW_STATE_MASK_CLOCKS) && remaining_buf_size > 0) {
		chars_printed = dcn10_get_clock_states(dc, pBuf, remaining_buf_size);
		pBuf += chars_printed;
		remaining_buf_size -= chars_printed;
	}
}