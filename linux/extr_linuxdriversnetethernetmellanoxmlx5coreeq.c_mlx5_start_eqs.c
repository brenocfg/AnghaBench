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
typedef  unsigned long long u64 ;
struct mlx5_eq_table {int /*<<< orphan*/  cmd_eq; int /*<<< orphan*/  async_eq; int /*<<< orphan*/  pages_eq; } ;
struct TYPE_2__ {struct mlx5_eq_table eq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 unsigned long long MLX5_ASYNC_EVENT_MASK ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN_MAX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_MCAM_REG (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  MLX5_EQ_TYPE_ASYNC ; 
 int /*<<< orphan*/  MLX5_EQ_VEC_ASYNC ; 
 int /*<<< orphan*/  MLX5_EQ_VEC_CMD ; 
 int /*<<< orphan*/  MLX5_EQ_VEC_PAGES ; 
 unsigned long long MLX5_EVENT_TYPE_CMD ; 
 unsigned long long MLX5_EVENT_TYPE_DCT_DRAINED ; 
 unsigned long long MLX5_EVENT_TYPE_DEVICE_TRACER ; 
 unsigned long long MLX5_EVENT_TYPE_FPGA_ERROR ; 
 unsigned long long MLX5_EVENT_TYPE_FPGA_QP_ERROR ; 
 unsigned long long MLX5_EVENT_TYPE_GENERAL_EVENT ; 
 unsigned long long MLX5_EVENT_TYPE_NIC_VPORT_CHANGE ; 
 int MLX5_EVENT_TYPE_PAGE_REQUEST ; 
 unsigned long long MLX5_EVENT_TYPE_PORT_MODULE_EVENT ; 
 unsigned long long MLX5_EVENT_TYPE_PPS_EVENT ; 
 unsigned long long MLX5_EVENT_TYPE_TEMP_WARN_EVENT ; 
 int MLX5_NUM_ASYNC_EQE ; 
 int MLX5_NUM_CMD_EQE ; 
 scalar_t__ MLX5_PPS_CAP (struct mlx5_core_dev*) ; 
 scalar_t__ MLX5_VPORT_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  dct ; 
 int /*<<< orphan*/  fpga ; 
 int /*<<< orphan*/  general_notification_event ; 
 int /*<<< orphan*/  mlx5_cmd_use_events (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cmd_use_polling (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 int mlx5_create_map_eq (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_destroy_unmap_eq (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  port_module_event ; 
 int /*<<< orphan*/  port_type ; 
 int /*<<< orphan*/  temp_warn_event ; 
 int /*<<< orphan*/  tracer_registers ; 

int mlx5_start_eqs(struct mlx5_core_dev *dev)
{
	struct mlx5_eq_table *table = &dev->priv.eq_table;
	u64 async_event_mask = MLX5_ASYNC_EVENT_MASK;
	int err;

	if (MLX5_VPORT_MANAGER(dev))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_NIC_VPORT_CHANGE);

	if (MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_ETH &&
	    MLX5_CAP_GEN(dev, general_notification_event))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_GENERAL_EVENT);

	if (MLX5_CAP_GEN(dev, port_module_event))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_PORT_MODULE_EVENT);
	else
		mlx5_core_dbg(dev, "port_module_event is not set\n");

	if (MLX5_PPS_CAP(dev))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_PPS_EVENT);

	if (MLX5_CAP_GEN(dev, fpga))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_FPGA_ERROR) |
				    (1ull << MLX5_EVENT_TYPE_FPGA_QP_ERROR);
	if (MLX5_CAP_GEN_MAX(dev, dct))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_DCT_DRAINED);

	if (MLX5_CAP_GEN(dev, temp_warn_event))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_TEMP_WARN_EVENT);

	if (MLX5_CAP_MCAM_REG(dev, tracer_registers))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_DEVICE_TRACER);

	err = mlx5_create_map_eq(dev, &table->cmd_eq, MLX5_EQ_VEC_CMD,
				 MLX5_NUM_CMD_EQE, 1ull << MLX5_EVENT_TYPE_CMD,
				 "mlx5_cmd_eq", MLX5_EQ_TYPE_ASYNC);
	if (err) {
		mlx5_core_warn(dev, "failed to create cmd EQ %d\n", err);
		return err;
	}

	mlx5_cmd_use_events(dev);

	err = mlx5_create_map_eq(dev, &table->async_eq, MLX5_EQ_VEC_ASYNC,
				 MLX5_NUM_ASYNC_EQE, async_event_mask,
				 "mlx5_async_eq", MLX5_EQ_TYPE_ASYNC);
	if (err) {
		mlx5_core_warn(dev, "failed to create async EQ %d\n", err);
		goto err1;
	}

	err = mlx5_create_map_eq(dev, &table->pages_eq,
				 MLX5_EQ_VEC_PAGES,
				 /* TODO: sriov max_vf + */ 1,
				 1 << MLX5_EVENT_TYPE_PAGE_REQUEST, "mlx5_pages_eq",
				 MLX5_EQ_TYPE_ASYNC);
	if (err) {
		mlx5_core_warn(dev, "failed to create pages EQ %d\n", err);
		goto err2;
	}

#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	if (MLX5_CAP_GEN(dev, pg)) {
		err = mlx5_create_map_eq(dev, &table->pfault_eq,
					 MLX5_EQ_VEC_PFAULT,
					 MLX5_NUM_ASYNC_EQE,
					 1 << MLX5_EVENT_TYPE_PAGE_FAULT,
					 "mlx5_page_fault_eq",
					 MLX5_EQ_TYPE_PF);
		if (err) {
			mlx5_core_warn(dev, "failed to create page fault EQ %d\n",
				       err);
			goto err3;
		}
	}

	return err;
err3:
	mlx5_destroy_unmap_eq(dev, &table->pages_eq);
#else
	return err;
#endif

err2:
	mlx5_destroy_unmap_eq(dev, &table->async_eq);

err1:
	mlx5_cmd_use_polling(dev);
	mlx5_destroy_unmap_eq(dev, &table->cmd_eq);
	return err;
}