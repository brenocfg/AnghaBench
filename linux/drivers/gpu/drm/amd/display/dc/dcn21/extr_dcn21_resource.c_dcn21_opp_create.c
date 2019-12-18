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
typedef  size_t uint32_t ;
struct output_pixel_processor {int dummy; } ;
struct dcn20_opp {struct output_pixel_processor base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcn20_opp_construct (struct dcn20_opp*,struct dc_context*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dcn20_opp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opp_mask ; 
 int /*<<< orphan*/ * opp_regs ; 
 int /*<<< orphan*/  opp_shift ; 

struct output_pixel_processor *dcn21_opp_create(
	struct dc_context *ctx, uint32_t inst)
{
	struct dcn20_opp *opp =
		kzalloc(sizeof(struct dcn20_opp), GFP_KERNEL);

	if (!opp) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	dcn20_opp_construct(opp, ctx, inst,
			&opp_regs[inst], &opp_shift, &opp_mask);
	return &opp->base;
}