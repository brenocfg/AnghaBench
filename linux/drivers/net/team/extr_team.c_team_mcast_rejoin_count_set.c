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
struct TYPE_4__ {int /*<<< orphan*/  u32_val; } ;
struct team_gsetter_ctx {TYPE_2__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct team {TYPE_1__ mcast_rejoin; } ;

/* Variables and functions */

__attribute__((used)) static int team_mcast_rejoin_count_set(struct team *team,
				       struct team_gsetter_ctx *ctx)
{
	team->mcast_rejoin.count = ctx->data.u32_val;
	return 0;
}