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
typedef  int u8 ;
struct mlx4_ib_dev {int num_ports; int ib_active; struct mlx4_dev* dev; int /*<<< orphan*/  ib_dev; } ;
struct mlx4_eqe {int dummy; } ;
struct TYPE_3__ {int flags2; } ;
struct mlx4_dev {int flags; TYPE_1__ caps; } ;
struct ib_event_work {int /*<<< orphan*/  work; struct mlx4_ib_dev* ib_dev; int /*<<< orphan*/  ib_eqe; } ;
struct TYPE_4__ {int port_num; } ;
struct ib_event {TYPE_2__ element; void* device; int /*<<< orphan*/  event; } ;
struct ib_device {int dummy; } ;
typedef  enum mlx4_dev_event { ____Placeholder_mlx4_dev_event } mlx4_dev_event ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IB_EVENT_DEVICE_FATAL ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  IB_LINK_LAYER_INFINIBAND ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int MLX4_DEV_CAP_FLAG2_SL_TO_VL_CHANGE_EVENT ; 
#define  MLX4_DEV_EVENT_CATASTROPHIC_ERROR 133 
#define  MLX4_DEV_EVENT_PORT_DOWN 132 
#define  MLX4_DEV_EVENT_PORT_MGMT_CHANGE 131 
#define  MLX4_DEV_EVENT_PORT_UP 130 
#define  MLX4_DEV_EVENT_SLAVE_INIT 129 
#define  MLX4_DEV_EVENT_SLAVE_SHUTDOWN 128 
 int MLX4_FLAG_SECURE_HOST ; 
 int /*<<< orphan*/  do_slave_init (struct mlx4_ib_dev*,int,int) ; 
 int /*<<< orphan*/  handle_bonded_port_state_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_port_mgmt_change_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 struct ib_event_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx4_eqe*,int) ; 
 int /*<<< orphan*/  mlx4_ib_handle_catas_error (struct mlx4_ib_dev*) ; 
 int /*<<< orphan*/  mlx4_ib_invalidate_all_guid_record (struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  mlx4_ib_slave_alias_guid_event (struct mlx4_ib_dev*,int,int,int) ; 
 scalar_t__ mlx4_is_bonded (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_master (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_slave (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_sched_ib_sl2vl_update_work (struct mlx4_ib_dev*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_port_get_link_layer (int /*<<< orphan*/ *,int) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static void mlx4_ib_event(struct mlx4_dev *dev, void *ibdev_ptr,
			  enum mlx4_dev_event event, unsigned long param)
{
	struct ib_event ibev;
	struct mlx4_ib_dev *ibdev = to_mdev((struct ib_device *) ibdev_ptr);
	struct mlx4_eqe *eqe = NULL;
	struct ib_event_work *ew;
	int p = 0;

	if (mlx4_is_bonded(dev) &&
	    ((event == MLX4_DEV_EVENT_PORT_UP) ||
	    (event == MLX4_DEV_EVENT_PORT_DOWN))) {
		ew = kmalloc(sizeof(*ew), GFP_ATOMIC);
		if (!ew)
			return;
		INIT_WORK(&ew->work, handle_bonded_port_state_event);
		ew->ib_dev = ibdev;
		queue_work(wq, &ew->work);
		return;
	}

	if (event == MLX4_DEV_EVENT_PORT_MGMT_CHANGE)
		eqe = (struct mlx4_eqe *)param;
	else
		p = (int) param;

	switch (event) {
	case MLX4_DEV_EVENT_PORT_UP:
		if (p > ibdev->num_ports)
			return;
		if (!mlx4_is_slave(dev) &&
		    rdma_port_get_link_layer(&ibdev->ib_dev, p) ==
			IB_LINK_LAYER_INFINIBAND) {
			if (mlx4_is_master(dev))
				mlx4_ib_invalidate_all_guid_record(ibdev, p);
			if (ibdev->dev->flags & MLX4_FLAG_SECURE_HOST &&
			    !(ibdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SL_TO_VL_CHANGE_EVENT))
				mlx4_sched_ib_sl2vl_update_work(ibdev, p);
		}
		ibev.event = IB_EVENT_PORT_ACTIVE;
		break;

	case MLX4_DEV_EVENT_PORT_DOWN:
		if (p > ibdev->num_ports)
			return;
		ibev.event = IB_EVENT_PORT_ERR;
		break;

	case MLX4_DEV_EVENT_CATASTROPHIC_ERROR:
		ibdev->ib_active = false;
		ibev.event = IB_EVENT_DEVICE_FATAL;
		mlx4_ib_handle_catas_error(ibdev);
		break;

	case MLX4_DEV_EVENT_PORT_MGMT_CHANGE:
		ew = kmalloc(sizeof *ew, GFP_ATOMIC);
		if (!ew)
			break;

		INIT_WORK(&ew->work, handle_port_mgmt_change_event);
		memcpy(&ew->ib_eqe, eqe, sizeof *eqe);
		ew->ib_dev = ibdev;
		/* need to queue only for port owner, which uses GEN_EQE */
		if (mlx4_is_master(dev))
			queue_work(wq, &ew->work);
		else
			handle_port_mgmt_change_event(&ew->work);
		return;

	case MLX4_DEV_EVENT_SLAVE_INIT:
		/* here, p is the slave id */
		do_slave_init(ibdev, p, 1);
		if (mlx4_is_master(dev)) {
			int i;

			for (i = 1; i <= ibdev->num_ports; i++) {
				if (rdma_port_get_link_layer(&ibdev->ib_dev, i)
					== IB_LINK_LAYER_INFINIBAND)
					mlx4_ib_slave_alias_guid_event(ibdev,
								       p, i,
								       1);
			}
		}
		return;

	case MLX4_DEV_EVENT_SLAVE_SHUTDOWN:
		if (mlx4_is_master(dev)) {
			int i;

			for (i = 1; i <= ibdev->num_ports; i++) {
				if (rdma_port_get_link_layer(&ibdev->ib_dev, i)
					== IB_LINK_LAYER_INFINIBAND)
					mlx4_ib_slave_alias_guid_event(ibdev,
								       p, i,
								       0);
			}
		}
		/* here, p is the slave id */
		do_slave_init(ibdev, p, 0);
		return;

	default:
		return;
	}

	ibev.device	      = ibdev_ptr;
	ibev.element.port_num = mlx4_is_bonded(ibdev->dev) ? 1 : (u8)p;

	ib_dispatch_event(&ibev);
}