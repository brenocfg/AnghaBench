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
struct dce_audio_shift {int dummy; } ;
struct dce_audio_registers {int dummy; } ;
struct dce_audio_mask {int dummy; } ;
struct audio {unsigned int inst; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dce_audio {struct audio base; struct dce_audio_mask const* masks; struct dce_audio_shift const* shifts; struct dce_audio_registers const* regs; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (struct dce_audio*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  funcs ; 
 struct dce_audio* kzalloc (int,int /*<<< orphan*/ ) ; 

struct audio *dce_audio_create(
		struct dc_context *ctx,
		unsigned int inst,
		const struct dce_audio_registers *reg,
		const struct dce_audio_shift *shifts,
		const struct dce_audio_mask *masks
		)
{
	struct dce_audio *audio = kzalloc(sizeof(*audio), GFP_KERNEL);

	if (audio == NULL) {
		ASSERT_CRITICAL(audio);
		return NULL;
	}

	audio->base.ctx = ctx;
	audio->base.inst = inst;
	audio->base.funcs = &funcs;

	audio->regs = reg;
	audio->shifts = shifts;
	audio->masks = masks;
	return &audio->base;
}