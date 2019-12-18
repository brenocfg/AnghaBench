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
struct mlx5_fpga_device {int state; int /*<<< orphan*/  mdev; int /*<<< orphan*/  state_lock; } ;
struct TYPE_2__ {void* raw; } ;
struct mlx5_eqe {TYPE_1__ data; } ;

/* Variables and functions */
#define  MLX5_EVENT_TYPE_FPGA_ERROR 130 
#define  MLX5_EVENT_TYPE_FPGA_QP_ERROR 129 
#define  MLX5_FPGA_STATUS_SUCCESS 128 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  fpga_error_event ; 
 int /*<<< orphan*/  fpga_qp_error_event ; 
 char* mlx5_fpga_qp_syndrome_to_string (int /*<<< orphan*/ ) ; 
 char* mlx5_fpga_syndrome_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn_ratelimited (struct mlx5_fpga_device*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mlx5_trigger_health_work (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mlx5_fpga_event(struct mlx5_fpga_device *fdev,
			   unsigned long event, void *eqe)
{
	void *data = ((struct mlx5_eqe *)eqe)->data.raw;
	const char *event_name;
	bool teardown = false;
	unsigned long flags;
	u8 syndrome;

	switch (event) {
	case MLX5_EVENT_TYPE_FPGA_ERROR:
		syndrome = MLX5_GET(fpga_error_event, data, syndrome);
		event_name = mlx5_fpga_syndrome_to_string(syndrome);
		break;
	case MLX5_EVENT_TYPE_FPGA_QP_ERROR:
		syndrome = MLX5_GET(fpga_qp_error_event, data, syndrome);
		event_name = mlx5_fpga_qp_syndrome_to_string(syndrome);
		break;
	default:
		return NOTIFY_DONE;
	}

	spin_lock_irqsave(&fdev->state_lock, flags);
	switch (fdev->state) {
	case MLX5_FPGA_STATUS_SUCCESS:
		mlx5_fpga_warn(fdev, "Error %u: %s\n", syndrome, event_name);
		teardown = true;
		break;
	default:
		mlx5_fpga_warn_ratelimited(fdev, "Unexpected error event %u: %s\n",
					   syndrome, event_name);
	}
	spin_unlock_irqrestore(&fdev->state_lock, flags);
	/* We tear-down the card's interfaces and functionality because
	 * the FPGA bump-on-the-wire is misbehaving and we lose ability
	 * to communicate with the network. User may still be able to
	 * recover by re-programming or debugging the FPGA
	 */
	if (teardown)
		mlx5_trigger_health_work(fdev->mdev);

	return NOTIFY_OK;
}