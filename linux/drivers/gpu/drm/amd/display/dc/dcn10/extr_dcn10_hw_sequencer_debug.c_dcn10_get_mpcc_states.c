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
struct resource_pool {int pipe_count; TYPE_2__* mpc; } ;
struct mpcc_state {int opp_id; int /*<<< orphan*/  idle; int /*<<< orphan*/  overlap_only; int /*<<< orphan*/  pre_multiplied_alpha; int /*<<< orphan*/  alpha_mode; int /*<<< orphan*/  mode; int /*<<< orphan*/  bot_mpcc_id; int /*<<< orphan*/  dpp_id; int /*<<< orphan*/  member_0; } ;
struct dc {struct resource_pool* res_pool; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_mpcc_state ) (TYPE_2__*,int,struct mpcc_state*) ;} ;

/* Variables and functions */
 unsigned int snprintf_count (char*,unsigned int,char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,struct mpcc_state*) ; 

__attribute__((used)) static unsigned int dcn10_get_mpcc_states(struct dc *dc, char *pBuf, unsigned int bufSize)
{
	struct resource_pool *pool = dc->res_pool;
	int i;

	unsigned int chars_printed = 0;
	unsigned int remaining_buffer = bufSize;

	chars_printed = snprintf_count(pBuf, remaining_buffer, "instance,opp,dpp,mpccbot,mode,alpha_mode,premult,overlap_only,idle\n");
	remaining_buffer -= chars_printed;
	pBuf += chars_printed;

	for (i = 0; i < pool->pipe_count; i++) {
		struct mpcc_state s = {0};

		pool->mpc->funcs->read_mpcc_state(pool->mpc, i, &s);

		if (s.opp_id != 0xf) {
			chars_printed = snprintf_count(pBuf, remaining_buffer, "%x,%x,%x,%x,%x,%x,%x,%x,%x\n",
				i, s.opp_id, s.dpp_id, s.bot_mpcc_id,
				s.mode, s.alpha_mode, s.pre_multiplied_alpha, s.overlap_only,
				s.idle);

			remaining_buffer -= chars_printed;
			pBuf += chars_printed;
		}
	}

	return bufSize - remaining_buffer;
}