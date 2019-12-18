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
struct mlx5e_priv {int dummy; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ESW_OFFLOAD ; 
 int /*<<< orphan*/  INGRESS ; 
 unsigned long MLX5_TC_FLAG (int /*<<< orphan*/ ) ; 
#define  TC_SETUP_CLSFLOWER 129 
#define  TC_SETUP_CLSMATCHALL 128 
 int mlx5e_rep_setup_tc_cls_flower (struct mlx5e_priv*,void*,unsigned long) ; 
 int mlx5e_rep_setup_tc_cls_matchall (struct mlx5e_priv*,void*) ; 

__attribute__((used)) static int mlx5e_rep_setup_tc_cb(enum tc_setup_type type, void *type_data,
				 void *cb_priv)
{
	unsigned long flags = MLX5_TC_FLAG(INGRESS) | MLX5_TC_FLAG(ESW_OFFLOAD);
	struct mlx5e_priv *priv = cb_priv;

	switch (type) {
	case TC_SETUP_CLSFLOWER:
		return mlx5e_rep_setup_tc_cls_flower(priv, type_data, flags);
	case TC_SETUP_CLSMATCHALL:
		return mlx5e_rep_setup_tc_cls_matchall(priv, type_data);
	default:
		return -EOPNOTSUPP;
	}
}