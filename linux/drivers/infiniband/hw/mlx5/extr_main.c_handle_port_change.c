#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_10__ {TYPE_4__* ports; } ;
struct mlx5_ib_dev {TYPE_5__ devr; int /*<<< orphan*/  ib_dev; } ;
struct TYPE_6__ {int port; } ;
struct TYPE_7__ {TYPE_1__ port; } ;
struct mlx5_eqe {int sub_type; TYPE_2__ data; } ;
struct TYPE_8__ {int port_num; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_3__ element; } ;
struct TYPE_9__ {int /*<<< orphan*/  pkey_change_work; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_EVENT_CLIENT_REREGISTER ; 
 int /*<<< orphan*/  IB_EVENT_GID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_LID_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PKEY_CHANGE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
 int /*<<< orphan*/  IB_LINK_LAYER_ETHERNET ; 
#define  MLX5_PORT_CHANGE_SUBTYPE_ACTIVE 134 
#define  MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG 133 
#define  MLX5_PORT_CHANGE_SUBTYPE_DOWN 132 
#define  MLX5_PORT_CHANGE_SUBTYPE_GUID 131 
#define  MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED 130 
#define  MLX5_PORT_CHANGE_SUBTYPE_LID 129 
#define  MLX5_PORT_CHANGE_SUBTYPE_PKEY 128 
 int /*<<< orphan*/  mlx5_ib_port_link_layer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_port_change(struct mlx5_ib_dev *ibdev, struct mlx5_eqe *eqe,
			      struct ib_event *ibev)
{
	u8 port = (eqe->data.port.port >> 4) & 0xf;

	ibev->element.port_num = port;

	switch (eqe->sub_type) {
	case MLX5_PORT_CHANGE_SUBTYPE_ACTIVE:
	case MLX5_PORT_CHANGE_SUBTYPE_DOWN:
	case MLX5_PORT_CHANGE_SUBTYPE_INITIALIZED:
		/* In RoCE, port up/down events are handled in
		 * mlx5_netdev_event().
		 */
		if (mlx5_ib_port_link_layer(&ibdev->ib_dev, port) ==
					    IB_LINK_LAYER_ETHERNET)
			return -EINVAL;

		ibev->event = (eqe->sub_type == MLX5_PORT_CHANGE_SUBTYPE_ACTIVE) ?
				IB_EVENT_PORT_ACTIVE : IB_EVENT_PORT_ERR;
		break;

	case MLX5_PORT_CHANGE_SUBTYPE_LID:
		ibev->event = IB_EVENT_LID_CHANGE;
		break;

	case MLX5_PORT_CHANGE_SUBTYPE_PKEY:
		ibev->event = IB_EVENT_PKEY_CHANGE;
		schedule_work(&ibdev->devr.ports[port - 1].pkey_change_work);
		break;

	case MLX5_PORT_CHANGE_SUBTYPE_GUID:
		ibev->event = IB_EVENT_GID_CHANGE;
		break;

	case MLX5_PORT_CHANGE_SUBTYPE_CLIENT_REREG:
		ibev->event = IB_EVENT_CLIENT_REREGISTER;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}