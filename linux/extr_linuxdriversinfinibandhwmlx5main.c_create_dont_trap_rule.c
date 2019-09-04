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
struct mlx5_ib_flow_prio {int /*<<< orphan*/  refcount; } ;
struct mlx5_ib_flow_handler {int /*<<< orphan*/  list; int /*<<< orphan*/  rule; } ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_flow_destination {int dummy; } ;
struct ib_flow_attr {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_ib_flow_handler*) ; 
 struct mlx5_ib_flow_handler* create_flow_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct ib_flow_attr*,struct mlx5_flow_destination*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_handler*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_ib_flow_handler *create_dont_trap_rule(struct mlx5_ib_dev *dev,
							  struct mlx5_ib_flow_prio *ft_prio,
							  struct ib_flow_attr *flow_attr,
							  struct mlx5_flow_destination *dst)
{
	struct mlx5_ib_flow_handler *handler_dst = NULL;
	struct mlx5_ib_flow_handler *handler = NULL;

	handler = create_flow_rule(dev, ft_prio, flow_attr, NULL);
	if (!IS_ERR(handler)) {
		handler_dst = create_flow_rule(dev, ft_prio,
					       flow_attr, dst);
		if (IS_ERR(handler_dst)) {
			mlx5_del_flow_rules(handler->rule);
			ft_prio->refcount--;
			kfree(handler);
			handler = handler_dst;
		} else {
			list_add(&handler_dst->list, &handler->list);
		}
	}

	return handler;
}