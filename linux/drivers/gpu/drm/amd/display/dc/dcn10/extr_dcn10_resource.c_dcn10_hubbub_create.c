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
struct dcn10_hubbub {struct hubbub base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hubbub1_construct (struct hubbub*,struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hubbub_mask ; 
 int /*<<< orphan*/  hubbub_reg ; 
 int /*<<< orphan*/  hubbub_shift ; 
 struct dcn10_hubbub* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hubbub *dcn10_hubbub_create(struct dc_context *ctx)
{
	struct dcn10_hubbub *dcn10_hubbub = kzalloc(sizeof(struct dcn10_hubbub),
					  GFP_KERNEL);

	if (!dcn10_hubbub)
		return NULL;

	hubbub1_construct(&dcn10_hubbub->base, ctx,
			&hubbub_reg,
			&hubbub_shift,
			&hubbub_mask);

	return &dcn10_hubbub->base;
}