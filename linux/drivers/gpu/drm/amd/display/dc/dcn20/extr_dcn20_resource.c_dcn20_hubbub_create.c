#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hubbub {int dummy; } ;
struct dcn20_vmid {int /*<<< orphan*/ * masks; int /*<<< orphan*/ * shifts; int /*<<< orphan*/ * regs; struct dc_context* ctx; } ;
struct dcn20_hubbub {struct hubbub base; struct dcn20_vmid* vmid; } ;
struct dc_context {int dummy; } ;
struct TYPE_2__ {int num_vmid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hubbub2_construct (struct dcn20_hubbub*,struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hubbub_mask ; 
 int /*<<< orphan*/  hubbub_reg ; 
 int /*<<< orphan*/  hubbub_shift ; 
 struct dcn20_hubbub* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ res_cap_nv10 ; 
 int /*<<< orphan*/  vmid_masks ; 
 int /*<<< orphan*/ * vmid_regs ; 
 int /*<<< orphan*/  vmid_shifts ; 

struct hubbub *dcn20_hubbub_create(struct dc_context *ctx)
{
	int i;
	struct dcn20_hubbub *hubbub = kzalloc(sizeof(struct dcn20_hubbub),
					  GFP_KERNEL);

	if (!hubbub)
		return NULL;

	hubbub2_construct(hubbub, ctx,
			&hubbub_reg,
			&hubbub_shift,
			&hubbub_mask);

	for (i = 0; i < res_cap_nv10.num_vmid; i++) {
		struct dcn20_vmid *vmid = &hubbub->vmid[i];

		vmid->ctx = ctx;

		vmid->regs = &vmid_regs[i];
		vmid->shifts = &vmid_shifts;
		vmid->masks = &vmid_masks;
	}

	return &hubbub->base;
}