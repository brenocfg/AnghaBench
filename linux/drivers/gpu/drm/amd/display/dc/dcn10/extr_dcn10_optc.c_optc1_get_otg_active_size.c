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
typedef  scalar_t__ uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_CONTROL ; 
 int /*<<< orphan*/  OTG_H_BLANK_END ; 
 int /*<<< orphan*/  OTG_H_BLANK_START ; 
 int /*<<< orphan*/  OTG_H_BLANK_START_END ; 
 int /*<<< orphan*/  OTG_MASTER_EN ; 
 int /*<<< orphan*/  OTG_V_BLANK_END ; 
 int /*<<< orphan*/  OTG_V_BLANK_START ; 
 int /*<<< orphan*/  OTG_V_BLANK_START_END ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 

bool optc1_get_otg_active_size(struct timing_generator *optc,
		uint32_t *otg_active_width,
		uint32_t *otg_active_height)
{
	uint32_t otg_enabled;
	uint32_t v_blank_start;
	uint32_t v_blank_end;
	uint32_t h_blank_start;
	uint32_t h_blank_end;
	struct optc *optc1 = DCN10TG_FROM_TG(optc);


	REG_GET(OTG_CONTROL,
			OTG_MASTER_EN, &otg_enabled);

	if (otg_enabled == 0)
		return false;

	REG_GET_2(OTG_V_BLANK_START_END,
			OTG_V_BLANK_START, &v_blank_start,
			OTG_V_BLANK_END, &v_blank_end);

	REG_GET_2(OTG_H_BLANK_START_END,
			OTG_H_BLANK_START, &h_blank_start,
			OTG_H_BLANK_END, &h_blank_end);

	*otg_active_width = v_blank_start - v_blank_end;
	*otg_active_height = h_blank_start - h_blank_end;
	return true;
}