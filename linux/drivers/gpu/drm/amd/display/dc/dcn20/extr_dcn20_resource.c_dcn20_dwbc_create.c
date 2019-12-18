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
typedef  int uint32_t ;
struct resource_pool {int /*<<< orphan*/ ** dwbc; TYPE_1__* res_cap; } ;
struct dcn20_dwbc {int /*<<< orphan*/  base; } ;
struct dc_context {int dummy; } ;
struct TYPE_2__ {int num_dwb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dcn20_dwbc_construct (struct dcn20_dwbc*,struct dc_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dm_error (char*) ; 
 int /*<<< orphan*/  dwbc20_mask ; 
 int /*<<< orphan*/ * dwbc20_regs ; 
 int /*<<< orphan*/  dwbc20_shift ; 
 struct dcn20_dwbc* kzalloc (int,int /*<<< orphan*/ ) ; 

bool dcn20_dwbc_create(struct dc_context *ctx, struct resource_pool *pool)
{
	int i;
	uint32_t pipe_count = pool->res_cap->num_dwb;

	ASSERT(pipe_count > 0);

	for (i = 0; i < pipe_count; i++) {
		struct dcn20_dwbc *dwbc20 = kzalloc(sizeof(struct dcn20_dwbc),
						    GFP_KERNEL);

		if (!dwbc20) {
			dm_error("DC: failed to create dwbc20!\n");
			return false;
		}
		dcn20_dwbc_construct(dwbc20, ctx,
				&dwbc20_regs[i],
				&dwbc20_shift,
				&dwbc20_mask,
				i);
		pool->dwbc[i] = &dwbc20->base;
	}
	return true;
}