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
typedef  int /*<<< orphan*/  uint32_t ;
struct scaler_data {int /*<<< orphan*/  v_active; int /*<<< orphan*/  h_active; } ;
struct dcn10_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTG_H_BLANK ; 
 int /*<<< orphan*/  OTG_H_BLANK_END ; 
 int /*<<< orphan*/  OTG_H_BLANK_START ; 
 int /*<<< orphan*/  OTG_V_BLANK ; 
 int /*<<< orphan*/  OTG_V_BLANK_END ; 
 int /*<<< orphan*/  OTG_V_BLANK_START ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpp1_dscl_set_otg_blank(
		struct dcn10_dpp *dpp, const struct scaler_data *data)
{
	uint32_t h_blank_start = data->h_active;
	uint32_t h_blank_end = 0;
	uint32_t v_blank_start = data->v_active;
	uint32_t v_blank_end = 0;

	REG_SET_2(OTG_H_BLANK, 0,
			OTG_H_BLANK_START, h_blank_start,
			OTG_H_BLANK_END, h_blank_end);

	REG_SET_2(OTG_V_BLANK, 0,
			OTG_V_BLANK_START, v_blank_start,
			OTG_V_BLANK_END, v_blank_end);
}