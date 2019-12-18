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
struct hubbub {int dummy; } ;
struct dcn_hubbub_wm_set {int wm_set; int /*<<< orphan*/  dram_clk_chanage; int /*<<< orphan*/  sr_exit; int /*<<< orphan*/  sr_enter; int /*<<< orphan*/  data_urgent; } ;
struct dcn_hubbub_wm {struct dcn_hubbub_wm_set* sets; } ;
struct dcn20_hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dcn20_hubbub* TO_DCN20_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  memset (struct dcn_hubbub_wm*,int /*<<< orphan*/ ,int) ; 

void hubbub21_wm_read_state(struct hubbub *hubbub,
		struct dcn_hubbub_wm *wm)
{
	struct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	struct dcn_hubbub_wm_set *s;

	memset(wm, 0, sizeof(struct dcn_hubbub_wm));

	s = &wm->sets[0];
	s->wm_set = 0;
	REG_GET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A,
			DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, &s->data_urgent);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A,
			DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A, &s->sr_enter);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A,
			DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A, &s->sr_exit);

	REG_GET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A,
			 DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, &s->dram_clk_chanage);

	s = &wm->sets[1];
	s->wm_set = 1;
	REG_GET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B,
			DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, &s->data_urgent);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B,
			DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B, &s->sr_enter);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B,
			DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B, &s->sr_exit);

	REG_GET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B,
			DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, &s->dram_clk_chanage);

	s = &wm->sets[2];
	s->wm_set = 2;
	REG_GET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C,
			DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, &s->data_urgent);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C,
			DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C, &s->sr_enter);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C,
			DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C, &s->sr_exit);

	REG_GET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C,
			DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, &s->dram_clk_chanage);

	s = &wm->sets[3];
	s->wm_set = 3;
	REG_GET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D,
			DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, &s->data_urgent);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D,
			DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D, &s->sr_enter);

	REG_GET(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D,
			DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D, &s->sr_exit);

	REG_GET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D,
			DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, &s->dram_clk_chanage);
}