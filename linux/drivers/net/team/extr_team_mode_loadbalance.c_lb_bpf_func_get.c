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
struct TYPE_8__ {int len; int /*<<< orphan*/ * ptr; } ;
struct TYPE_5__ {TYPE_4__ bin_val; } ;
struct team_gsetter_ctx {TYPE_1__ data; } ;
struct team {int dummy; } ;
struct sock_filter {int dummy; } ;
struct lb_priv {TYPE_3__* ex; } ;
struct TYPE_7__ {TYPE_2__* orig_fprog; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/ * filter; } ;

/* Variables and functions */
 struct lb_priv* get_lb_priv (struct team*) ; 

__attribute__((used)) static int lb_bpf_func_get(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);

	if (!lb_priv->ex->orig_fprog) {
		ctx->data.bin_val.len = 0;
		ctx->data.bin_val.ptr = NULL;
		return 0;
	}
	ctx->data.bin_val.len = lb_priv->ex->orig_fprog->len *
				sizeof(struct sock_filter);
	ctx->data.bin_val.ptr = lb_priv->ex->orig_fprog->filter;
	return 0;
}