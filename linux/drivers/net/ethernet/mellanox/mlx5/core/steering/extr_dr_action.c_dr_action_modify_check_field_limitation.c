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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct mlx5dr_domain {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_NIC_RX ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_NIC_TX ; 
 scalar_t__ MLX5_ACTION_IN_FIELD_METADATA_REG_A ; 
 scalar_t__ MLX5_ACTION_IN_FIELD_METADATA_REG_B ; 
 scalar_t__ MLX5_ACTION_IN_FIELD_OUT_IPV6_HOPLIMIT ; 
 scalar_t__ MLX5_ACTION_IN_FIELD_OUT_IP_TTL ; 
 scalar_t__ MLX5_ACTION_IN_FIELD_OUT_TCP_ACK_NUM ; 
 scalar_t__ MLX5_ACTION_IN_FIELD_OUT_TCP_SEQ_NUM ; 
 scalar_t__ MLX5_ACTION_TYPE_ADD ; 
 scalar_t__ MLX5_ACTION_TYPE_SET ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  action_type ; 
 int /*<<< orphan*/  field ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5dr_info (struct mlx5dr_domain*,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_action_in ; 

__attribute__((used)) static int
dr_action_modify_check_field_limitation(struct mlx5dr_domain *dmn,
					const __be64 *sw_action)
{
	u16 sw_field;
	u8 action;

	sw_field = MLX5_GET(set_action_in, sw_action, field);
	action = MLX5_GET(set_action_in, sw_action, action_type);

	/* Check if SW field is supported in current domain (RX/TX) */
	if (action == MLX5_ACTION_TYPE_SET) {
		if (sw_field == MLX5_ACTION_IN_FIELD_METADATA_REG_A) {
			if (dmn->type != MLX5DR_DOMAIN_TYPE_NIC_TX) {
				mlx5dr_dbg(dmn, "Unsupported field %d for RX/FDB set action\n",
					   sw_field);
				return -EINVAL;
			}
		}

		if (sw_field == MLX5_ACTION_IN_FIELD_METADATA_REG_B) {
			if (dmn->type != MLX5DR_DOMAIN_TYPE_NIC_RX) {
				mlx5dr_dbg(dmn, "Unsupported field %d for TX/FDB set action\n",
					   sw_field);
				return -EINVAL;
			}
		}
	} else if (action == MLX5_ACTION_TYPE_ADD) {
		if (sw_field != MLX5_ACTION_IN_FIELD_OUT_IP_TTL &&
		    sw_field != MLX5_ACTION_IN_FIELD_OUT_IPV6_HOPLIMIT &&
		    sw_field != MLX5_ACTION_IN_FIELD_OUT_TCP_SEQ_NUM &&
		    sw_field != MLX5_ACTION_IN_FIELD_OUT_TCP_ACK_NUM) {
			mlx5dr_dbg(dmn, "Unsupported field %d for add action\n", sw_field);
			return -EINVAL;
		}
	} else {
		mlx5dr_info(dmn, "Unsupported action %d modify action\n", action);
		return -EOPNOTSUPP;
	}

	return 0;
}