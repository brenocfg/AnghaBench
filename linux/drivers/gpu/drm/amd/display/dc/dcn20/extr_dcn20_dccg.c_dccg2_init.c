#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* ctx; } ;
struct dcn_dccg {TYPE_4__ base; } ;
struct dccg {int dummy; } ;
struct TYPE_7__ {TYPE_2__* dc; } ;
struct TYPE_6__ {TYPE_1__* res_pool; } ;
struct TYPE_5__ {int pipe_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPPCLK_DTO_CTRL ; 
 int /*<<< orphan*/ * DPPCLK_DTO_DB_EN ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn_dccg* TO_DCN_DCCG (struct dccg*) ; 

void dccg2_init(struct dccg *dccg)
{
	struct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);

	// Fallthrough intentional to program all available dpp_dto's
	switch (dccg_dcn->base.ctx->dc->res_pool->pipe_count) {
	case 6:
		REG_UPDATE(DPPCLK_DTO_CTRL, DPPCLK_DTO_DB_EN[5], 1);
		/* Fall through */
	case 5:
		REG_UPDATE(DPPCLK_DTO_CTRL, DPPCLK_DTO_DB_EN[4], 1);
		/* Fall through */
	case 4:
		REG_UPDATE(DPPCLK_DTO_CTRL, DPPCLK_DTO_DB_EN[3], 1);
		/* Fall through */
	case 3:
		REG_UPDATE(DPPCLK_DTO_CTRL, DPPCLK_DTO_DB_EN[2], 1);
		/* Fall through */
	case 2:
		REG_UPDATE(DPPCLK_DTO_CTRL, DPPCLK_DTO_DB_EN[1], 1);
		/* Fall through */
	case 1:
		REG_UPDATE(DPPCLK_DTO_CTRL, DPPCLK_DTO_DB_EN[0], 1);
		break;
	default:
		ASSERT(false);
		break;
	}
}