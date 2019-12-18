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
typedef  unsigned long long u64 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 unsigned long long MLX5_ASYNC_EVENT_MASK ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_GEN_MAX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_MCAM_REG (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 unsigned long long MLX5_EVENT_TYPE_DCT_DRAINED ; 
 unsigned long long MLX5_EVENT_TYPE_DEVICE_TRACER ; 
 unsigned long long MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED ; 
 unsigned long long MLX5_EVENT_TYPE_FPGA_ERROR ; 
 unsigned long long MLX5_EVENT_TYPE_FPGA_QP_ERROR ; 
 unsigned long long MLX5_EVENT_TYPE_GENERAL_EVENT ; 
 unsigned long long MLX5_EVENT_TYPE_MONITOR_COUNTER ; 
 unsigned long long MLX5_EVENT_TYPE_NIC_VPORT_CHANGE ; 
 unsigned long long MLX5_EVENT_TYPE_PORT_MODULE_EVENT ; 
 unsigned long long MLX5_EVENT_TYPE_PPS_EVENT ; 
 unsigned long long MLX5_EVENT_TYPE_TEMP_WARN_EVENT ; 
 scalar_t__ MLX5_PPS_CAP (struct mlx5_core_dev*) ; 
 scalar_t__ MLX5_VPORT_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  dct ; 
 int /*<<< orphan*/  event_cap ; 
 int /*<<< orphan*/  fpga ; 
 int /*<<< orphan*/  gather_user_async_events (struct mlx5_core_dev*,unsigned long long*) ; 
 int /*<<< orphan*/  general_notification_event ; 
 int /*<<< orphan*/  max_num_of_monitor_counters ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*) ; 
 scalar_t__ mlx5_eswitch_is_funcs_handler (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  port_module_event ; 
 int /*<<< orphan*/  temp_warn_event ; 
 int /*<<< orphan*/  tracer_registers ; 

__attribute__((used)) static void gather_async_events_mask(struct mlx5_core_dev *dev, u64 mask[4])
{
	u64 async_event_mask = MLX5_ASYNC_EVENT_MASK;

	if (MLX5_VPORT_MANAGER(dev))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_NIC_VPORT_CHANGE);

	if (MLX5_CAP_GEN(dev, general_notification_event))
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

	if (MLX5_CAP_GEN(dev, max_num_of_monitor_counters))
		async_event_mask |= (1ull << MLX5_EVENT_TYPE_MONITOR_COUNTER);

	if (mlx5_eswitch_is_funcs_handler(dev))
		async_event_mask |=
			(1ull << MLX5_EVENT_TYPE_ESW_FUNCTIONS_CHANGED);

	mask[0] = async_event_mask;

	if (MLX5_CAP_GEN(dev, event_cap))
		gather_user_async_events(dev, mask);
}