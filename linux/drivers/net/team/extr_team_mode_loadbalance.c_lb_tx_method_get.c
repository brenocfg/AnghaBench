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
struct TYPE_2__ {char* str_val; } ;
struct team_gsetter_ctx {TYPE_1__ data; } ;
struct team {int /*<<< orphan*/  lock; } ;
struct lb_priv {int /*<<< orphan*/  select_tx_port_func; } ;
typedef  int /*<<< orphan*/  lb_select_tx_port_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct lb_priv* get_lb_priv (struct team*) ; 
 char* lb_select_tx_port_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lb_tx_method_get(struct team *team, struct team_gsetter_ctx *ctx)
{
	struct lb_priv *lb_priv = get_lb_priv(team);
	lb_select_tx_port_func_t *func;
	char *name;

	func = rcu_dereference_protected(lb_priv->select_tx_port_func,
					 lockdep_is_held(&team->lock));
	name = lb_select_tx_port_get_name(func);
	BUG_ON(!name);
	ctx->data.str_val = name;
	return 0;
}