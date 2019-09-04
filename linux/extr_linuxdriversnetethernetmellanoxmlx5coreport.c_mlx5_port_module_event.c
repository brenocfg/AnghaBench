#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/ * error_counters; int /*<<< orphan*/ * status_counters; } ;
struct mlx5_priv {TYPE_2__ pme_stats; } ;
struct mlx5_eqe_port_module {int module_status; int error_type; int /*<<< orphan*/  module; } ;
struct TYPE_3__ {struct mlx5_eqe_port_module port_module; } ;
struct mlx5_eqe {TYPE_1__ data; } ;
struct mlx5_core_dev {struct mlx5_priv priv; } ;
typedef  enum port_module_event_status_type { ____Placeholder_port_module_event_status_type } port_module_event_status_type ;
typedef  enum port_module_event_error_type { ____Placeholder_port_module_event_error_type } port_module_event_error_type ;

/* Variables and functions */
 int MLX5_MODULE_EVENT_ERROR_UNKNOWN ; 
 int MLX5_MODULE_STATUS_ERROR ; 
 int PORT_MODULE_EVENT_ERROR_TYPE_MASK ; 
 int PORT_MODULE_EVENT_MODULE_STATUS_MASK ; 
 int /*<<< orphan*/  mlx5_core_info (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * mlx5_pme_error ; 
 int /*<<< orphan*/ * mlx5_pme_status ; 
 int /*<<< orphan*/  printk_ratelimit () ; 

void mlx5_port_module_event(struct mlx5_core_dev *dev, struct mlx5_eqe *eqe)
{
	enum port_module_event_status_type module_status;
	enum port_module_event_error_type error_type;
	struct mlx5_eqe_port_module *module_event_eqe;
	struct mlx5_priv *priv = &dev->priv;
	u8 module_num;

	module_event_eqe = &eqe->data.port_module;
	module_num = module_event_eqe->module;
	module_status = module_event_eqe->module_status &
			PORT_MODULE_EVENT_MODULE_STATUS_MASK;
	error_type = module_event_eqe->error_type &
		     PORT_MODULE_EVENT_ERROR_TYPE_MASK;

	if (module_status < MLX5_MODULE_STATUS_ERROR) {
		priv->pme_stats.status_counters[module_status - 1]++;
	} else if (module_status == MLX5_MODULE_STATUS_ERROR) {
		if (error_type >= MLX5_MODULE_EVENT_ERROR_UNKNOWN)
			/* Unknown error type */
			error_type = MLX5_MODULE_EVENT_ERROR_UNKNOWN;
		priv->pme_stats.error_counters[error_type]++;
	}

	if (!printk_ratelimit())
		return;

	if (module_status < MLX5_MODULE_STATUS_ERROR)
		mlx5_core_info(dev,
			       "Port module event: module %u, %s\n",
			       module_num, mlx5_pme_status[module_status - 1]);

	else if (module_status == MLX5_MODULE_STATUS_ERROR)
		mlx5_core_info(dev,
			       "Port module event[error]: module %u, %s, %s\n",
			       module_num, mlx5_pme_status[module_status - 1],
			       mlx5_pme_error[error_type]);
}