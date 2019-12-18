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
struct timing_generator {size_t inst; struct dc_context* ctx; } ;
struct optc {struct timing_generator base; int /*<<< orphan*/ * tg_mask; int /*<<< orphan*/ * tg_shift; int /*<<< orphan*/ * tg_regs; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcn20_timing_generator_init (struct optc*) ; 
 struct optc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg_mask ; 
 int /*<<< orphan*/ * tg_regs ; 
 int /*<<< orphan*/  tg_shift ; 

struct timing_generator *dcn20_timing_generator_create(
		struct dc_context *ctx,
		uint32_t instance)
{
	struct optc *tgn10 =
		kzalloc(sizeof(struct optc), GFP_KERNEL);

	if (!tgn10)
		return NULL;

	tgn10->base.inst = instance;
	tgn10->base.ctx = ctx;

	tgn10->tg_regs = &tg_regs[instance];
	tgn10->tg_shift = &tg_shift;
	tgn10->tg_mask = &tg_mask;

	dcn20_timing_generator_init(tgn10);

	return &tgn10->base;
}