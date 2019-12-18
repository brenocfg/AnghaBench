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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {struct mlx5_ib_dev* dev; int /*<<< orphan*/  sub_type; int /*<<< orphan*/  pkt_reformat; } ;
struct mlx5_ib_flow_action {TYPE_1__ flow_action_raw; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
typedef  enum mlx5_flow_namespace_type { ____Placeholder_mlx5_flow_namespace_type } mlx5_flow_namespace_type ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_IB_FLOW_ACTION_PACKET_REFORMAT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int mlx5_ib_dv_to_prm_packet_reforamt_type (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5_ib_ft_type_to_namespace (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mlx5_packet_reformat_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*,int) ; 

__attribute__((used)) static int mlx5_ib_flow_action_create_packet_reformat_ctx(
	struct mlx5_ib_dev *dev,
	struct mlx5_ib_flow_action *maction,
	u8 ft_type, u8 dv_prt,
	void *in, size_t len)
{
	enum mlx5_flow_namespace_type namespace;
	u8 prm_prt;
	int ret;

	ret = mlx5_ib_ft_type_to_namespace(ft_type, &namespace);
	if (ret)
		return ret;

	ret = mlx5_ib_dv_to_prm_packet_reforamt_type(dv_prt, &prm_prt);
	if (ret)
		return ret;

	maction->flow_action_raw.pkt_reformat =
		mlx5_packet_reformat_alloc(dev->mdev, prm_prt, len,
					   in, namespace);
	if (IS_ERR(maction->flow_action_raw.pkt_reformat)) {
		ret = PTR_ERR(maction->flow_action_raw.pkt_reformat);
		return ret;
	}

	maction->flow_action_raw.sub_type =
		MLX5_IB_FLOW_ACTION_PACKET_REFORMAT;
	maction->flow_action_raw.dev = dev;

	return 0;
}