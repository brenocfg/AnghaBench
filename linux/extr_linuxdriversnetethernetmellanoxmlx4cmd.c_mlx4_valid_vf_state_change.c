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
struct mlx4_vport_state {int default_qos; int default_vlan; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  member_0; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int MLX4_VGT ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*,...) ; 
 scalar_t__ mlx4_is_vf_vst_and_prio_qos (struct mlx4_dev*,int,struct mlx4_vport_state*) ; 

__attribute__((used)) static bool mlx4_valid_vf_state_change(struct mlx4_dev *dev, int port,
				       struct mlx4_vport_state *vf_admin,
				       int vlan, int qos)
{
	struct mlx4_vport_state dummy_admin = {0};

	if (!mlx4_is_vf_vst_and_prio_qos(dev, port, vf_admin) ||
	    !vf_admin->tx_rate)
		return true;

	dummy_admin.default_qos = qos;
	dummy_admin.default_vlan = vlan;

	/* VF wants to move to other VST state which is valid with current
	 * rate limit. Either differnt default vlan in VST or other
	 * supported QoS priority. Otherwise we don't allow this change when
	 * the TX rate is still configured.
	 */
	if (mlx4_is_vf_vst_and_prio_qos(dev, port, &dummy_admin))
		return true;

	mlx4_info(dev, "Cannot change VF state to %s while rate is set\n",
		  (vlan == MLX4_VGT) ? "VGT" : "VST");

	if (vlan != MLX4_VGT)
		mlx4_info(dev, "VST priority %d not supported for QoS\n", qos);

	mlx4_info(dev, "Please set rate to 0 prior to this VF state change\n");

	return false;
}