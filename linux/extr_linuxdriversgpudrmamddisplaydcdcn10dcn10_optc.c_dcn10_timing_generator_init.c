#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * funcs; } ;
struct optc {int min_h_blank; int min_v_blank; int min_v_blank_interlace; int min_h_sync_width; int min_v_sync_width; TYPE_2__* tg_mask; scalar_t__ max_v_total; scalar_t__ max_h_total; TYPE_1__ base; } ;
struct TYPE_4__ {scalar_t__ OTG_V_TOTAL; scalar_t__ OTG_H_TOTAL; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcn10_tg_funcs ; 

void dcn10_timing_generator_init(struct optc *optc1)
{
	optc1->base.funcs = &dcn10_tg_funcs;

	optc1->max_h_total = optc1->tg_mask->OTG_H_TOTAL + 1;
	optc1->max_v_total = optc1->tg_mask->OTG_V_TOTAL + 1;

	optc1->min_h_blank = 32;
	optc1->min_v_blank = 3;
	optc1->min_v_blank_interlace = 5;
	optc1->min_h_sync_width = 8;
	optc1->min_v_sync_width = 1;
}