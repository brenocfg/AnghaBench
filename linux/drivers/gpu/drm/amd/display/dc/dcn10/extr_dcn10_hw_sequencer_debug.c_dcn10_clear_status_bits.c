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
 int /*<<< orphan*/  dcn10_clear_hubp_underflow (struct dc*) ; 
 int /*<<< orphan*/  dcn10_clear_otpc_underflow (struct dc*) ; 

void dcn10_clear_status_bits(struct dc *dc, unsigned int mask)
{
	/*
	 *  Mask Format
	 *  Bit 0 - 31: Status bit to clear
	 *
	 *  Mask = 0x0 means clear all status bits
	 */
	const unsigned int DC_HW_STATE_MASK_HUBP_UNDERFLOW	= 0x1;
	const unsigned int DC_HW_STATE_MASK_OTPC_UNDERFLOW	= 0x2;

	if (mask == 0x0)
		mask = 0xFFFFFFFF;

	if (mask & DC_HW_STATE_MASK_HUBP_UNDERFLOW)
		dcn10_clear_hubp_underflow(dc);

	if (mask & DC_HW_STATE_MASK_OTPC_UNDERFLOW)
		dcn10_clear_otpc_underflow(dc);
}