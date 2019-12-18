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
struct TYPE_2__ {int /*<<< orphan*/  nb; } ;
struct mlx5_eswitch {scalar_t__ mode; TYPE_1__ esw_funcs; int /*<<< orphan*/  dev; int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESW_FUNCTIONS_CHANGED ; 
 scalar_t__ MLX5_ESWITCH_OFFLOADS ; 
 int /*<<< orphan*/  MLX5_NB_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIC_VPORT_CHANGE ; 
 int /*<<< orphan*/  eswitch_vport_event ; 
 int /*<<< orphan*/  mlx5_eq_notifier_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_esw_funcs_changed_handler ; 
 scalar_t__ mlx5_eswitch_is_funcs_handler (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_eswitch_event_handlers_register(struct mlx5_eswitch *esw)
{
	MLX5_NB_INIT(&esw->nb, eswitch_vport_event, NIC_VPORT_CHANGE);
	mlx5_eq_notifier_register(esw->dev, &esw->nb);

	if (esw->mode == MLX5_ESWITCH_OFFLOADS && mlx5_eswitch_is_funcs_handler(esw->dev)) {
		MLX5_NB_INIT(&esw->esw_funcs.nb, mlx5_esw_funcs_changed_handler,
			     ESW_FUNCTIONS_CHANGED);
		mlx5_eq_notifier_register(esw->dev, &esw->esw_funcs.nb);
	}
}