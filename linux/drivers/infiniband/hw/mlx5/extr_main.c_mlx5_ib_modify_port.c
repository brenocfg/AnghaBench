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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mlx5_ib_dev {int /*<<< orphan*/  cap_mask_mutex; int /*<<< orphan*/  mdev; } ;
struct ib_port_modify {int clr_port_cap_mask; int set_port_cap_mask; } ;
struct ib_port_attr {int port_cap_flags; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_INFINIBAND ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 int /*<<< orphan*/  ib_virt ; 
 scalar_t__ mlx5_ib_port_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 
 int mlx5_set_port_caps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_port_caps_atomic (struct mlx5_ib_dev*,int /*<<< orphan*/ ,int,int) ; 
 struct mlx5_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static int mlx5_ib_modify_port(struct ib_device *ibdev, u8 port, int mask,
			       struct ib_port_modify *props)
{
	struct mlx5_ib_dev *dev = to_mdev(ibdev);
	struct ib_port_attr attr;
	u32 tmp;
	int err;
	u32 change_mask;
	u32 value;
	bool is_ib = (mlx5_ib_port_link_layer(ibdev, port) ==
		      IB_LINK_LAYER_INFINIBAND);

	/* CM layer calls ib_modify_port() regardless of the link layer. For
	 * Ethernet ports, qkey violation and Port capabilities are meaningless.
	 */
	if (!is_ib)
		return 0;

	if (MLX5_CAP_GEN(dev->mdev, ib_virt) && is_ib) {
		change_mask = props->clr_port_cap_mask | props->set_port_cap_mask;
		value = ~props->clr_port_cap_mask | props->set_port_cap_mask;
		return set_port_caps_atomic(dev, port, change_mask, value);
	}

	mutex_lock(&dev->cap_mask_mutex);

	err = ib_query_port(ibdev, port, &attr);
	if (err)
		goto out;

	tmp = (attr.port_cap_flags | props->set_port_cap_mask) &
		~props->clr_port_cap_mask;

	err = mlx5_set_port_caps(dev->mdev, port, tmp);

out:
	mutex_unlock(&dev->cap_mask_mutex);
	return err;
}