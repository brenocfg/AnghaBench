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
struct input_pixel_processor {int dummy; } ;
struct dcn10_ipp {struct input_pixel_processor base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcn20_ipp_construct (struct dcn10_ipp*,struct dc_context*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipp_mask ; 
 int /*<<< orphan*/ * ipp_regs ; 
 int /*<<< orphan*/  ipp_shift ; 
 struct dcn10_ipp* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct input_pixel_processor *dcn21_ipp_create(
	struct dc_context *ctx, uint32_t inst)
{
	struct dcn10_ipp *ipp =
		kzalloc(sizeof(struct dcn10_ipp), GFP_KERNEL);

	if (!ipp) {
		BREAK_TO_DEBUGGER();
		return NULL;
	}

	dcn20_ipp_construct(ipp, ctx, inst,
			&ipp_regs[inst], &ipp_shift, &ipp_mask);
	return &ipp->base;
}