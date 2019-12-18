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
struct mlx5_ib_flow_handler {int /*<<< orphan*/  rule; int /*<<< orphan*/  list; } ;
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_flow_destination {int dummy; } ;
struct ib_flow_attr {int size; int /*<<< orphan*/  num_of_specs; } ;
typedef  int /*<<< orphan*/  flow_attr ;

/* Variables and functions */
 struct mlx5_ib_flow_handler* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mlx5_ib_flow_handler*) ; 
 int PTR_ERR (struct mlx5_ib_flow_handler*) ; 
 struct mlx5_ib_flow_handler* create_flow_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct ib_flow_attr const*,struct mlx5_flow_destination*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_handler*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_ib_flow_handler *create_sniffer_rule(struct mlx5_ib_dev *dev,
							struct mlx5_ib_flow_prio *ft_rx,
							struct mlx5_ib_flow_prio *ft_tx,
							struct mlx5_flow_destination *dst)
{
	struct mlx5_ib_flow_handler *handler_rx;
	struct mlx5_ib_flow_handler *handler_tx;
	int err;
	static const struct ib_flow_attr flow_attr  = {
		.num_of_specs = 0,
		.size = sizeof(flow_attr)
	};

	handler_rx = create_flow_rule(dev, ft_rx, &flow_attr, dst);
	if (IS_ERR(handler_rx)) {
		err = PTR_ERR(handler_rx);
		goto err;
	}

	handler_tx = create_flow_rule(dev, ft_tx, &flow_attr, dst);
	if (IS_ERR(handler_tx)) {
		err = PTR_ERR(handler_tx);
		goto err_tx;
	}

	list_add(&handler_tx->list, &handler_rx->list);

	return handler_rx;

err_tx:
	mlx5_del_flow_rules(handler_rx->rule);
	ft_rx->refcount--;
	kfree(handler_rx);
err:
	return ERR_PTR(err);
}