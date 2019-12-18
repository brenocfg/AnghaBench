#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int len; int /*<<< orphan*/ * ptr; } ;
struct TYPE_9__ {TYPE_2__ bin_val; } ;
struct team_gsetter_ctx {TYPE_3__ data; TYPE_1__* info; } ;
struct team {int dummy; } ;
struct lb_stats {int dummy; } ;
struct lb_priv {TYPE_6__* ex; } ;
struct TYPE_11__ {TYPE_4__* info; } ;
struct TYPE_12__ {TYPE_5__ stats; } ;
struct TYPE_10__ {int /*<<< orphan*/  stats; } ;
struct TYPE_7__ {unsigned char array_index; } ;

/* Variables and functions */
 struct lb_priv* get_lb_priv (struct team*) ; 

__attribute__((used)) static int lb_hash_stats_get(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	unsigned char hash = ctx->info->array_index;

	ctx->data.bin_val.ptr = &lb_priv->ex->stats.info[hash].stats;
	ctx->data.bin_val.len = sizeof(struct lb_stats);
	return 0;
}